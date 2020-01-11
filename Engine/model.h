#pragma once
#include "std/xf_vmath_mat.h"
#include "vertex_array.h"
#include "texture.h"

class model
{
    vao mesh;
    texture tex; // read texture path from xml file
    mat4 xform;
public:
    model(const char*);
    void draw();
};
