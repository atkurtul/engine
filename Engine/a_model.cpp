#include "a_model.h"
#include "shader.h"
#include "buffer.h"

void a_model::handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv)
{
    for (xml_node* n : nodes)
    {
        xfstr* name = namearray.find(n->attribs["sid"]);
        int id = name - namearray.begin();
        binds[id] = n->getChild("matrix")->readDataAsMat4<float>().front();
        bone* b = new bone(id, *name, inv[id], xforms[id], binds[id]);
        v.push(b);
        auto children = n->getChildren("node", "type", "JOINT");
        handleBones(b->children, children, namearray, inv);
    }
}

void a_model::addAnim(const char* path)
{
    xml_parser p(path);
    //animation
    auto animroot = p.root.getDescendant("animation", "id", "action_container");
    animations.push({});
    animation& anim = animations.back();
    for (xfstr& n : namearray)
    {
        auto in = animroot->getDescendant("float_array", "id", n + "_pose_matrix-input-array");
        auto out = animroot->getDescendant("float_array", "id", n + "_pose_matrix-output-array");

        if (in && out)
        {
            uint id = &n - namearray.begin();
            auto inv = in->readDataAs<float>();
            auto outv = out->readDataAsMat4<float>();
            if (inv.back() > anim.len) anim.len = inv.back();
            anim.frames[id] = { (xfvec<float>&&)inv, (xfvec<mat4>&&)outv };
        }
    }

}

a_model::a_model(const char* path)
{
    xml_parser p(path);
    //geometry
    auto vertices = p.root.getDescendant("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
    auto normals = p.root.getDescendant("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
    auto textures = p.root.getDescendant("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
    uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
    auto indicesroot = p.root.getDescendant("mesh")->getChildren("triangles");
    xfvec<uint> indices;
    for (auto triangles : indicesroot)
    {
        auto v = triangles->getChild("p")->readDataAs<uint>();
        for (uint u : v) indices.push(u);
    }
    //controllers
    namearray = p.root.getDescendant("Name_array", "id", "skin-joints-array")->readDataAsStr();
    invbinds = p.root.getDescendant("float_array", "id", "skin-bind_poses-array")->readDataAsMat4<float>();
    auto weights = p.root.getDescendant("float_array", "id", "skin-weights-array")->readDataAs<float>();
    auto vcount = p.root.getDescendant("vcount")->readDataAs<uint>();
    auto vs = p.root.getDescendant("v")->readDataAs<uint>();
    auto sorted = sortWeights(weights, vcount, vs);

    //bone hierarchy
    xforms.resize(namearray.size());
    binds.resize(namearray.size());
    auto boneroot = p.root.getDescendant("node", "id", "Armature");
    auto ourBones = boneroot->getChildren("node", "type", "JOINT");
    handleBones(bones, ourBones, namearray, invbinds);
    struct layout
    {
        vec3 v;
        vec3 n;
        vec2 t;
        uvec3 j;
        vec3 w;
    };

    xfvec<layout> finalbuffer;
    for (uint i = 0; i < indices.size(); i += dim) {

        finalbuffer.push(
            {
                vertices[indices[i]],
                normals[indices[i + 1]], // normal
                textures[indices[i + 2]], // uv
                sorted[indices[i]].first, // joint index
                sorted[indices[i]].second // joint weight
            });
    }
    mesh.gen();
    buffer(finalbuffer);
    mesh.attrib(0, 3, 14, 0);
    mesh.attrib(1, 3, 14, 3);
    mesh.attrib(2, 2, 14, 6);
    mesh.attribI(3, 3, 14, 8);
    mesh.attrib(4, 3, 14, 11);
    mesh.size = finalbuffer.size();
}

void a_model::update()
{
    animations[activeAnimation].update();
    for (bone* b : bones) b->setPose(animations[activeAnimation], m4id);
}

void a_model::draw()
{
    update();
    mesh.bind();
    tex.bind();
    uniform("xform", xform);
    uniform("bones", xforms);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}

xfvec<xfcouple<uvec3, vec3>> a_model::sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v)
{
    struct weight
    {
        uint i;
        float w;
        bool operator <= (const weight& W) { return w <= W.w; }
    };
    xfvec<xfcouple<uvec3, vec3>> re;
    uint current = 0;
    for (uint i : vcount) {
        xfvec<weight> temp;
        for (uint j = 0; j < i * 2; j += 2)
            temp.push({ v[j + current * 2], weights[v[j + 1 + current * 2]] });
        temp.sort();
        temp.reverse();
        xfcouple<uvec3, vec3> t;
        for (uint j = 0; j < 3 && j < temp.size(); ++j)
        {
            t.first[j] = temp[j].i;
            t.second[j] = temp[j].w;
        }
        float l = 1.f / (t.second.x + t.second.y + t.second.z);
        t.second.x *= l;
        t.second.y *= l;
        t.second.z *= l;
        re.push(t);
        current += i;
    }
    return re;
}