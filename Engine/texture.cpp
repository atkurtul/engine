#include "window.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::texture(const char* path) 
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int w, h, d;
	unsigned char* data = stbi_load(path, &w, &h, &d, 0);
	_size = vec3(w, h, d);
	if (data)
	{
		if (d == 4) 
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else 
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
}

texture::texture(const texture& t)
	: _id(t._id), _size(t._size)
{
}

texture& texture::operator=(const texture& t)
{
	_id = t._id;
	_size = t._size;
	return *this;
}

void texture::bind() 
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

texture::operator uint() const
{
	return _id;
}