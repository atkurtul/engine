#include "xml.h"

xml_node::xml_node() 
{
}

xml_node::xml_node(xfstr node)
{
    if (node.find(' '))
    {
        name = node.inbtwn(node[0], ' ');
        name.cls();
        node.erase(node.find(' '), node.rend());
        while (node.find("="))
        {
            attribs[node.substr(0, node.find('=') - node.begin())] = node.exbtwn('"', '"');
            node.erase(node.find('"', 2), node.rend());
            node.cls();
        }
    }
    else name = node;
}

void xml_node::addChild(xml_node* n)
{
    n->parent = this;
    auto a = children.find(n->name);
    if (a)  a->push(n);
    else  children[n->name] = { n };
}

int xml_node::childCount()
{
    int i = 0;
    for (auto& a : children)
        i += a.v.size();
    return i;
}

xfvec<xml_node*> xml_node::getChildren(const xfstr& cname)
{
    return children[cname];
}

xfvec<xml_node*> xml_node::getChildren(const xfstr& cname, const xfstr& key, const xfstr& val)
{
    xfvec<xml_node*> re;
    xfvec<xml_node*> search = children[cname];
    for (xml_node* n : search)
    {
        auto a = n->attribs.find(key);
        if (a) if (*a == val || a->find(val)) re.push(n);
    }
    return re;
}

xml_node* xml_node::getChild(const xfstr& name)
{
    auto* c = children.find(name);
    if (c) return c->front();
    return 0;
}

xml_node* xml_node::getChild(const xfstr& cname, const xfstr& key, const xfstr& val)
{
    auto* c = children.find(cname);
    if (c) {
        for (xml_node* n : *c)
        {
            auto* a = n->attribs.find(key);
            if (a)
                if (*a == val || a->find(val)) return n;
        }
    }
    return 0;
}

xml_node* xml_node::getDescendant(const xfstr& cname)
{
    auto* c = getChild(cname);
    if (c) return c;
    for (auto& p : children)
    {
        for (auto& pp : p.v)
        {
            c = pp->getDescendant(cname);
            if (c) return c;
        }
    }
    return 0;
}

xml_node* xml_node::getDescendant(const xfstr& cname, const xfstr& key, const xfstr& val)
{
    auto* c = getChild(cname, key, val);
    if (c) return c;
    for (auto& p : children)
    {
        for (auto& pp : p.v)
        {
            c = pp->getDescendant(cname, key, val);
            if (c) return c;
        }
    }
    return 0;
}


xfvec<xfstr> xml_node::readDataAsStr()
{
    xfstr arr = data;
    xfvec<xfstr> re;
    while (arr.find(' '))
    {
        re.push(arr.substr(0, arr.find(' ') - arr.begin()));
        arr.erase(arr.find(' '), arr.rend());
    }
    re.push((xfstr&&)arr);
    return re;
}

template<class T>
xfvec<T> xml_node::readDataAs()
{
    xfstr arr = data;
    xfvec<T> re;
    while (arr.size() > 0)
    {
        re.emplace(0);
        arr >> re.back();
    }
    return re;
}

template<class T, uint n>
xfvec<vec<T, n>> xml_node::readDataAsVec()
{
    xfstr arr = data;
    xfvec<vec<T, n>> re;
    while (arr.size() > 0)
    {
        re.push({});
        for (int i = 0; i < n; ++i) arr >> re.back()[i];
    }
    return re;
}

template<class T>
xfvec<matrix4<T>> xml_node::readDataAsMat4()
{
    return (xfvec<matrix4<T>>&)readDataAsVec<float, 16>();
}

xml_parser::xml_parser(const char* path)
{
    xfstr xml;
    if (xml.read(path).empty()) return;

    root = xml.exbtwn('<', '>');
    xml_node* current_node = &root;


    xml.erase(xml.find('>'), xml.rend());
    xml.cls();
    char* closing = xml.find('>');
    while (closing)
    {
        xfstr name = xml.exbtwn('<', '>');
        xml.erase(xml.find('>'), xml.rend());
        xml.cls();
        if (name[0] == '/')
        {
            current_node = current_node->parent;
            closing = xml.find('>');
            continue;
        }
        if (*name.rbegin() == '/')
        {
            name.erase(name.rbegin());
            xml_node* new_node = new xml_node(name);
            current_node->addChild(new_node);
            continue;
        }
        if (name[0] != '/' && *name.rbegin() != '/')
        {
            xml_node* new_node = new xml_node(name);
            if (xml[0] != '<' && !xml.empty())
            {
                new_node->data = xml.substr(0, xml.find('<') - xml.begin()).cls();
                current_node->addChild(new_node);

                xml.erase(xml.find('>'), xml.rend());
                xml.cls();
                closing = xml.find('>');
                continue;
            }
            current_node->addChild(new_node);
            current_node = new_node;
            closing = xml.find('>');
            continue;
        }
    }
}

template xfvec<matrix4<uint>> xml_node::readDataAsMat4();
template xfvec<matrix4<float>> xml_node::readDataAsMat4();
template xfvec<vec<float, 4>> xml_node::readDataAsVec();
template xfvec<vec<float, 3>> xml_node::readDataAsVec();
template xfvec<vec<float, 2>> xml_node::readDataAsVec();
template xfvec<vec<uint, 4>> xml_node::readDataAsVec();
template xfvec<vec<uint, 3>> xml_node::readDataAsVec();
template xfvec<vec<uint, 2>> xml_node::readDataAsVec();
template xfvec<float> xml_node::readDataAs();
template xfvec<uint> xml_node::readDataAs();