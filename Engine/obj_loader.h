#pragma once
#include "std/xf_vmath_vec.h"
#include "vertex_array.h"
#include "buffer.h"

struct obj_loader
{
	vao operator()(const char* path, vec3 col = 0);
};