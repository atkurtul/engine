#pragma once
#include "vertex_array.h"
#include "texture.h"

struct font
{
	struct Char
	{
		float advance;
		vao quad;
	};
	float line;
	texture atlas;
	Char charmap[128];
	font(const char* path, float scale = 0.12f);
};