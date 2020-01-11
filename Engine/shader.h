#pragma once
#include "std/xf_vmath_mat.h"
#include "std/xf_vec.h"

class shader 
{
	uint _id;
	uint compile(const char* path, int type);
	static uint compile_str(const char* str, int type);
	inline static uint active = -1;
	static void status(uint);
	static void pstatus(uint);
public:
	shader();
	shader(const char* cs_path);
	shader(const char* vs_path, const char* fs_path);
	shader(const shader&);
	shader(uint);
	shader& operator =(const shader&);
	static shader create(const char* vs, const char* fs);
	void use();
	operator uint() const;
	void uniform(const char* uni, const vec2& v);
	void uniform(const char* uni, const vec3& v);
	void uniform(const char* uni, const vec4& v);
	void uniform(const char* uni, const mat2& m);
	void uniform(const char* uni, const mat3& m);
	void uniform(const char* uni, const mat4& m);
	void uniform(const char* uni, const xfvec<vec2>& v);
	void uniform(const char* uni, const xfvec<vec3>& v);
	void uniform(const char* uni, const xfvec<vec4>& v);
	void uniform(const char* uni, const xfvec<mat2>& v);
	void uniform(const char* uni, const xfvec<mat3>& v);
	void uniform(const char* uni, const xfvec<mat4>& v);
	void uniform(const char* uni, float x);
	void uniform(const char* uni, int x);
	void uniform(const char* uni, uint x);
	void uniform(const char* uni, float x, float y);
	void uniform(const char* uni, int x, int y);
	void uniform(const char* uni, uint x, uint y);
	void uniform(const char* uni, float x, float y, float z);
	void uniform(const char* uni, int x, int y, int z);
	void uniform(const char* uni, uint x, uint y, uint z);
	void uniform(const char* uni, float x, float y, float z, float w);
	void uniform(const char* uni, int x, int y, int z, int w);
	void uniform(const char* uni, uint x, uint y, uint z, uint w);

	template<class T>
	friend void uniform(const char* uni, const T& v);

	friend void uniform(const char* uni, int);
	friend void uniform(const char* uni, uint);
	friend void uniform(const char* uni, float);

	template<class T>
	friend void uniform(const char* uni, T, T);

	template<class T>
	friend void uniform(const char* uni, T, T, T);

	template<class T>
	friend void uniform(const char* uni, T, T, T, T);

};

template<class T>
inline void uniform(const char* uni, const T& v)
{
	shader(shader::active).uniform(uni, v);
}

inline void uniform(const char* uni, int x)
{
	shader(shader::active).uniform(uni, x);
}

inline void uniform(const char* uni, uint x)
{
	shader(shader::active).uniform(uni, x);
}

inline void uniform(const char* uni, float x)
{
	shader(shader::active).uniform(uni, x);
}

template<class T>
inline void uniform(const char* uni, T x, T y)
{
	shader(shader::active).uniform(uni, x, y);
}

template<class T>
inline void uniform(const char* uni, T x, T y, T z)
{
	shader(shader::active).uniform(uni, x, y, z);
}

template<class T>
inline void uniform(const char* uni, T x, T y, T z, T w)
{
	shader(shader::active).uniform(uni, x, y, z, w);
}
