#pragma once
#include "std/xf_str.h"
#include "std/xf_map.h"
#include "std/xf_vmath_mat.h"

class xml_node
{
public:
    xfstr name;
    xfstr data;
    xml_node* parent = nullptr;
    xfmap<xfstr, xfstr> attribs;
    xfmap<xfstr, xfvec<xml_node*>> children;

    xfvec<xfstr> readDataAsStr();
    template<class T>
    xfvec<T> readDataAs();
    template<class T, uint n>
    xfvec<vec<T, n>> readDataAsVec();
    template<class T>
    xfvec<matrix4<T>> readDataAsMat4();

    xml_node();
    xml_node(xfstr node);
    void addChild(xml_node* n);
    int childCount();
    xfvec<xml_node*> getChildren(const xfstr& cname);
    xfvec<xml_node*> getChildren(const xfstr& cname, const xfstr& key, const xfstr& val);
    xml_node* getChild(const xfstr& name);
    xml_node* getChild(const xfstr& cname, const xfstr& key, const xfstr& val);
    xml_node* getDescendant(const xfstr& cname);
    xml_node* getDescendant(const xfstr& cname, const xfstr& key, const xfstr& val);
};

class xml_parser
{
public:
    xml_node root;
    xml_parser(const char* path);
};
