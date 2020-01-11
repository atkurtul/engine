#include "model.h"
#include "xml.h"
#include "buffer.h"
#include "shader.h"

model::model(const char* path)
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
    struct layout
    {
        vec3 v;
        vec3 n;
        vec2 t;
    };
    xfvec<layout> finalbuffer;
    for (int i = 0; i < indices.size(); i += dim) {

        finalbuffer.push(
            {
                vertices[indices[i]],
                normals[indices[i + 1]], // normal
                textures[indices[i + 2]], // uv
            });
    }
    mesh.gen();
    buffer(finalbuffer);
    mesh.attrib(0, 3, 8, 0);
    mesh.attrib(1, 3, 8, 3);
    mesh.attrib(2, 2, 8, 6);
    mesh.size = finalbuffer.size();
}

void model::draw()
{
    mesh.bind();
    tex.bind();
    uniform("xform", xform);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}

