#pragma once
#include "std/xf_vec.h"
#include "glad/glad.h"

template<class T>
inline unsigned buffer(const xfvec<T>& verts, int type = GL_ARRAY_BUFFER) 
{
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, verts.size() * sizeof(T), verts.data(), GL_STATIC_DRAW);
	return vbo;
}

template<class T>
inline unsigned buffer(unsigned alloc, int type = GL_ARRAY_BUFFER)
{
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, alloc * sizeof(T), 0, GL_DYNAMIC_DRAW);
	return vbo;
}
