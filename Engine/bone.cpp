#include "bone.h"

bone::bone(uint id, xfstr& name, mat4& inv, mat4& anim, mat4& bind)
    :
    parent(nullptr),
    id(id),
    name(name),
    inv(inv),
    anim(anim),
    bind(bind)
{
}

void bone::setPose(const animation& animation, const mat4& parentxf)
{
    mat4* pose = animation.frames[id].getPoseAt(animation.t);
    if (pose)
    {
        mat4 bound = parentxf * *pose;
        delete pose;
        anim = bound * inv;
        for (bone* b : children) b->setPose(animation, bound);
        return;
    }
    mat4 bound = parentxf * bind;
    anim = bound * inv;
    for (bone* b : children) b->setPose(animation, bound);
}
