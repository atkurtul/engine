#pragma once
#include "animation.h"

struct bone
{
    uint id;
    bone* parent;
    xfvec<bone*> children;
    mat4& inv;
    mat4& anim;
    mat4& bind;
    xfstr& name;
    bone(uint id, xfstr& name, mat4& inv, mat4& anim, mat4& bind);
    void setPose(const animation& animation, const mat4& parentxf);
};
