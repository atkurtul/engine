#pragma once
#include "std/xf_map.h"
#include "std/xf_vmath_quaternion.h"

struct frame
{
    xfvec<float> input;
    xfvec<mat4> output;
    mat4* getPoseAt(float t) const;
};

struct animation
{
    xfmap<uint, frame> frames;
    float len = 0.f;
    mutable float t = 0.f;
    void update() const;
};