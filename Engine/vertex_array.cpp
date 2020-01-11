#include "window.h"
#include "vertex_array.h"

vao::vao()
	: _id(-1), size(0)
{
}

vao::vao(const vao& v)
	: _id(v._id), size(v.size)
{
}

vao& vao::operator=(const vao& v)
{
	_id = v._id;
	size = v.size;
	return *this;
}

void vao::gen()
{
	glGenVertexArrays(1, &_id);
	glBindVertexArray(_id);
}

void vao::bind()
{
	glBindVertexArray(_id);
}

vao::operator uint() const
{
	return _id;
}

void vao::attrib(uint layout, uint size, uint stride, uint ptr)
{
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride * 4, (void*)(ptr * 4));
}

void vao::attribI(uint layout, uint size, uint stride, uint ptr)
{
	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, GL_UNSIGNED_INT, stride * 4, (void*)(ptr * 4));
}