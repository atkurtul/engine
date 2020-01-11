#pragma once
#include "std/xf_vmath_vec.h"
class texture 
{
	unsigned _id;
	vec3	_size;
public:
	texture() : _id(-1) {}
	texture(const char* path);
	texture(const texture&);
	texture& operator = (const texture&);
	void bind();
	operator uint() const;

	const vec3& size = _size;
};
