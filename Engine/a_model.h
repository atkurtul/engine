#pragma once
#include "std/xf_couple.h"
#include "vertex_array.h"
#include "texture.h"
#include "bone.h"
#include "xml.h"

class a_model
{
    vao mesh;
    texture tex; // read texture path from xml file
    mat4 xform;
    xfvec<bone*> bones;
    xfvec<mat4>  xforms;
    xfvec<xfstr> namearray;
    xfvec<mat4>  invbinds;
    xfvec<mat4>  binds;
    xfvec<animation> animations;
    uint activeAnimation = 0;
    void handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv);
    xfvec<xfcouple<uvec3, vec3>> sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v);
    void update();

public:
    a_model(const char* model);
    void draw();
    void addAnim(const char* path);

};