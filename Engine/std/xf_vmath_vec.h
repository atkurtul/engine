#pragma once
#include "xf_vmath_swizz.h"

template<class T, uint n>
struct vec : type_proxy<base, T, n>::type
{
	using base = typename type_proxy<base, T, n>::type;
	using base::operator=;
	vec& operator=(const vec& v);
	vec();
	T data[n];
};

template<class T>
struct vec<T, 2> : base<T, 0, 1> {
	using base<T, 0, 1>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y);
	vec(const vec& v);

	template<class T2>
	vec(const vec<T2, 2>&);

	template<uint a, uint b>
	vec(const base<T, a, b>& v);
	union {
		T data[2];
		struct { T x, y; };
		swizz<T, 0, 1> xy;
		swizz<T, 1, 0> yx;
	};
};

template<class T>
struct vec<T, 3> : base<T, 0, 1, 2> {
	using base<T, 0, 1, 2>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y, T z);
	vec(const vec& v);
	template<class T2>
	vec(const vec<T2, 3>&);
	template<uint a, uint b, uint c>
	vec(const base<T, a, b, c>& v);
	template<uint a, uint b>
	vec(T x, const base<T, a, b>& v);
	template<uint a, uint b>
	vec(const base<T, a, b>& v, T z);
	union {
		T data[3];
		struct { T x, y, z; };
		swizz<T, 0, 1> xy;
		swizz<T, 0, 2> xz;
		swizz<T, 1, 0> yx;
		swizz<T, 1, 2> yz;
		swizz<T, 2, 0> zx;
		swizz<T, 2, 1> zy;
		swizz<T, 0, 1, 2> xyz;
		swizz<T, 0, 2, 1> xzy;
		swizz<T, 1, 0, 2> yxz;
		swizz<T, 1, 2, 0> yzx;
		swizz<T, 2, 0, 1> zxy;
		swizz<T, 2, 1, 0> zyx;
	};
};

template<class T>
struct vec<T, 4> : base<T, 0, 1, 2, 3> {
	using base<T, 0, 1, 2, 3>::operator=;
	vec& operator=(const vec& v);
	vec();
	vec(T x);
	vec(T x, T y, T z, T w);
	vec(const vec& v);
	template<class T2>
	vec(const vec<T2, 4>&);
	template<uint a, uint b, uint c, uint d>
	vec(const base<T, a, b, c, d>& v);
	template<uint a, uint b>
	vec(T x, T y, const base<T, a, b>& v);
	template<uint a, uint b>
	vec(const base<T, a, b>& v, T z, T w);
	template<uint a, uint b>
	vec(T x, const base<T, a, b>& v, T w);
	template<uint a, uint b, uint c, uint d>
	vec(const base<T, a, b>& l, const base<T, c, d>& r);
	template<uint a, uint b, uint c>
	vec(const base<T, a, b, c>& v, T w);
	template<uint a, uint b, uint c>
	vec(T x, const base<T, a, b, c>& v);
	union {
		T data[4];
		struct { T x, y, z, w; };
		swizz<T, 0, 1> xy;
		swizz<T, 0, 2> xz;
		swizz<T, 0, 3> xw;
		swizz<T, 1, 0> yx;
		swizz<T, 1, 2> yz;
		swizz<T, 1, 3> yw;
		swizz<T, 2, 0> zx;
		swizz<T, 2, 1> zy;
		swizz<T, 2, 3> zw;
		swizz<T, 3, 0> wx;
		swizz<T, 3, 1> wy;
		swizz<T, 3, 2> wz;
		swizz<T, 0, 1, 2> xyz;
		swizz<T, 0, 1, 3> xyw;
		swizz<T, 0, 2, 1> xzy;
		swizz<T, 0, 2, 3> xzw;
		swizz<T, 0, 3, 1> xwy;
		swizz<T, 0, 3, 2> xwz;
		swizz<T, 1, 0, 2> yxz;
		swizz<T, 1, 0, 3> yxw;
		swizz<T, 1, 2, 0> yzx;
		swizz<T, 1, 2, 3> yzw;
		swizz<T, 1, 3, 0> ywx;
		swizz<T, 1, 3, 2> ywz;
		swizz<T, 2, 0, 1> zxy;
		swizz<T, 2, 0, 3> zxw;
		swizz<T, 2, 1, 0> zyx;
		swizz<T, 2, 1, 3> zyw;
		swizz<T, 2, 3, 0> zwx;
		swizz<T, 2, 3, 1> zwy;
		swizz<T, 3, 0, 1> wxy;
		swizz<T, 3, 0, 2> wxz;
		swizz<T, 3, 1, 0> wyx;
		swizz<T, 3, 1, 2> wyz;
		swizz<T, 3, 2, 0> wzx;
		swizz<T, 3, 2, 1> wzy;
		swizz<T, 0, 1, 2, 3> xyzw;
		swizz<T, 0, 1, 3, 2> xywz;
		swizz<T, 0, 2, 1, 3> xzyw;
		swizz<T, 0, 2, 3, 1> xzwy;
		swizz<T, 0, 3, 1, 2> xwyz;
		swizz<T, 0, 3, 2, 1> xwzy;
		swizz<T, 1, 0, 2, 3> yxzw;
		swizz<T, 1, 0, 3, 2> yxwz;
		swizz<T, 1, 2, 0, 3> yzxw;
		swizz<T, 1, 2, 3, 0> yzwx;
		swizz<T, 1, 3, 0, 2> ywxz;
		swizz<T, 1, 3, 2, 0> ywzx;
		swizz<T, 2, 0, 1, 3> zxyw;
		swizz<T, 2, 0, 3, 1> zxwy;
		swizz<T, 2, 1, 0, 3> zyxw;
		swizz<T, 2, 1, 3, 0> zywx;
		swizz<T, 2, 3, 0, 1> zwxy;
		swizz<T, 2, 3, 1, 0> zwyx;
		swizz<T, 3, 0, 1, 2> wxyz;
		swizz<T, 3, 0, 2, 1> wxzy;
		swizz<T, 3, 1, 0, 2> wyxz;
		swizz<T, 3, 1, 2, 0> wyzx;
		swizz<T, 3, 2, 0, 1> wzxy;
		swizz<T, 3, 2, 1, 0> wzyx;
	};
};


template<class T, uint n>
vec<T, n>& vec<T, n>::operator=(const vec& v)
{
	return (vec&)base::operator=(v);
}

template<class T, uint n>
inline vec<T, n>::vec()
{
}

template<class T>
inline vec<T, 2>& vec<T, 2>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

template<class T>
inline vec<T, 2>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 2>::vec(T x)
	: data{ x, x }
{
}

template<class T>
inline vec<T, 2>::vec(T x, T y)
	: data{ x, y }
{
}

template<class T>
inline vec<T, 2>::vec(const vec& v)
	: data{ v.x, v.y }
{
}

template<class T>
template<class T2>
inline vec<T, 2>::vec(const vec<T2, 2>& v)
	: data{ T(v.x), T(v.y) }
{

}

template<class T>
template<uint a, uint b>
inline vec<T, 2>::vec(const base<T, a, b>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b) }
{
}

template<class T>
inline vec<T, 3>& vec<T, 3>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

template<class T>
inline vec<T, 3>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 3>::vec(T x)
	: data{ x, x, x }
{
}

template<class T>
inline vec<T, 3>::vec(T x, T y, T z)
	: data{ x, y, z }
{
}

template<class T>
inline vec<T, 3>::vec(const vec& v)
	: data{ v.x, v.y, v.z }
{
}

template<class T>
template<class T2>
inline vec<T, 3>::vec(const vec<T2, 3>& v)
	: data{ T(v.x), T(v.y), T(v.z) }
{

}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 3>::vec(const base<T, a, b, c>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 3>::vec(T x, const base<T, a, b>& v)
	: data{ x, *(T*)(&v + a), *(T*)(&v + b) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 3>::vec(const base<T, a, b>& v, T z)
	: data{ *(T*)(&v + a), *(T*)(&v + b), z }
{
}

template<class T>
inline vec<T, 4>& vec<T, 4>::operator=(const vec& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

template<class T>
inline vec<T, 4>::vec()
	: data{}
{
}

template<class T>
inline vec<T, 4>::vec(T x)
	: data{ x, x, x, x }
{
}

template<class T>
inline vec<T, 4>::vec(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline vec<T, 4>::vec(const vec& v)
	: data{ v.x, v.y, v.z, v.w }
{
}

template<class T>
template<class T2>
inline vec<T, 4>::vec(const vec<T2, 4>& v)
	: data{ T(v.x), T(v.y), T(v.z), T(v.w) }
{

}

template<class T>
template<uint a, uint b, uint c, uint d>
inline vec<T, 4>::vec(const base<T, a, b, c, d>& v)
	: data{ *(T*)(&v + a), *(T*)(&v + b),  *(T*)(&v + c), *(T*)(&v + d) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(T x, T y, const base<T, a, b>& v)
	: data{ x, y, *(T*)(&v + a),*(T*)(&v + b) }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(const base<T, a, b>& v, T z, T w)
	: data{ *(T*)(&v + a),*(T*)(&v + b), z, w }
{
}

template<class T>
template<uint a, uint b>
inline vec<T, 4>::vec(T x, const base<T, a, b>& v, T w)
	: data{ x, *(T*)(&v + a),*(T*)(&v + b), w }
{
}

template<class T>
template<uint a, uint b, uint c, uint d>
inline vec<T, 4>::vec(const base<T, a, b>& l, const base<T, c, d>& r)
	: data{ *(T*)(&l + a),*(T*)(&l + b), *(T*)(&r + c), *(T*)(&r + d) }
{
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 4>::vec(const base<T, a, b, c>& v, T w)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c), w }
{
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 4>::vec(T x, const base<T, a, b, c>& v)
	: data{ x, *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c) }
{
}

