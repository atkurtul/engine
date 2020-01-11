#pragma once

class vao 
{
	unsigned _id;
public:
	unsigned size;
	vao();
	vao(const vao&);
	vao& operator = (const vao&);
	void gen();
	void bind();
	operator unsigned() const;
	void attrib(unsigned layout, unsigned size, unsigned stride = 0, unsigned ptr = 0);
	void attribI(unsigned layout, unsigned size, unsigned stride = 0, unsigned ptr = 0);
};
