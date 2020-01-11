#pragma once
#include "xf_vmath_base.h"

template <class T, uint x>
struct alignas(sizeof(T)) swizz<T, x>
{
	T& operator  =(T f);
	T& operator +=(T f);
	T& operator -=(T f);
	T& operator *=(T f);
	T& operator /=(T f);
	operator T& ();
	operator T() const;
};

template<class T, uint x, uint y>
struct swizz<T, x, y> : base<T, x, y> {
	using base<T, x, y>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b>
	swizz& operator=(const swizz<T, a, b>&);
	union {
		base<T, x, y> xy;
		base<T, y, x> yx;
		swizz<T, x> x;
		swizz<T, y> y;
	};
};

template<class T, uint x, uint y, uint z>
struct swizz<T, x, y, z> : base<T, x, y, z> {
	using base<T, x, y, z>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b, uint c>
	swizz& operator=(const swizz<T, a, b, c>&);
	union {
		swizz<T, x, y> xy;
		swizz<T, x, z> xz;
		swizz<T, y, x> yx;
		swizz<T, y, z> yz;
		swizz<T, z, x> zx;
		swizz<T, z, y> zy;
		base<T, x, y, z> xyz;
		base<T, x, z, y> xzy;
		base<T, y, x, z> yxz;
		base<T, y, z, x> yzx;
		base<T, z, x, y> zxy;
		base<T, z, y, x> zyx;
		swizz<T, x> x;
		swizz<T, y> y;
		swizz<T, z> z;
	};
};

template<class T, uint x, uint y, uint z, uint w>
struct swizz<T, x, y, z, w> : base<T, x, y, z, w> {
	using base<T, x, y, z, w>::operator=;
	swizz& operator=(const swizz&);
	template<uint a, uint b, uint c, uint d>
	swizz& operator=(const swizz<T, a, b, c, d>&);
	union {
		swizz<T, x, y> xy;
		swizz<T, x, z> xz;
		swizz<T, x, w> xw;
		swizz<T, y, x> yx;
		swizz<T, y, z> yz;
		swizz<T, y, w> yw;
		swizz<T, z, x> zx;
		swizz<T, z, y> zy;
		swizz<T, z, w> zw;
		swizz<T, w, x> wx;
		swizz<T, w, y> wy;
		swizz<T, w, z> wz;
		swizz<T, x, y, z> xyz;
		swizz<T, x, y, w> xyw;
		swizz<T, x, z, y> xzy;
		swizz<T, x, z, w> xzw;
		swizz<T, x, w, y> xwy;
		swizz<T, x, w, z> xwz;
		swizz<T, y, x, z> yxz;
		swizz<T, y, x, w> yxw;
		swizz<T, y, z, x> yzx;
		swizz<T, y, z, w> yzw;
		swizz<T, y, w, x> ywx;
		swizz<T, y, w, z> ywz;
		swizz<T, z, x, y> zxy;
		swizz<T, z, x, w> zxw;
		swizz<T, z, y, x> zyx;
		swizz<T, z, y, w> zyw;
		swizz<T, z, w, x> zwx;
		swizz<T, z, w, y> zwy;
		swizz<T, w, x, y> wxy;
		swizz<T, w, x, z> wxz;
		swizz<T, w, y, x> wyx;
		swizz<T, w, y, z> wyz;
		swizz<T, w, z, x> wzx;
		swizz<T, w, z, y> wzy;
		base<T, x, y, z, w> xyzw;
		base<T, x, y, w, z> xywz;
		base<T, x, z, y, w> xzyw;
		base<T, x, z, w, y> xzwy;
		base<T, x, w, y, z> xwyz;
		base<T, x, w, z, y> xwzy;
		base<T, y, x, z, w> yxzw;
		base<T, y, x, w, z> yxwz;
		base<T, y, z, x, w> yzxw;
		base<T, y, z, w, x> yzwx;
		base<T, y, w, x, z> ywxz;
		base<T, y, w, z, x> ywzx;
		base<T, z, x, y, w> zxyw;
		base<T, z, x, w, y> zxwy;
		base<T, z, y, x, w> zyxw;
		base<T, z, y, w, x> zywx;
		base<T, z, w, x, y> zwxy;
		base<T, z, w, y, x> zwyx;
		base<T, w, x, y, z> wxyz;
		base<T, w, x, z, y> wxzy;
		base<T, w, y, x, z> wyxz;
		base<T, w, y, z, x> wyzx;
		base<T, w, z, x, y> wzxy;
		base<T, w, z, y, x> wzyx;
		swizz<T, x> x;
		swizz<T, y> y;
		swizz<T, z> z;
		swizz<T, w> w;
	};
};


template<class T, uint x>
inline T& swizz<T, x>::operator=(T f)
{
	return *(T*)(this + x) = f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator+=(T f)
{
	return *(T*)(this + x) += f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator-=(T f)
{
	return *(T*)(this + x) -= f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator*=(T f)
{
	return *(T*)(this + x) *= f;
}

template<class T, uint x>
inline T& swizz<T, x>::operator/=(T f)
{
	return *(T*)(this + x) /= f;
}

template<class T, uint x>
inline swizz<T, x>::operator T& ()
{
	return *(T*)(this + x);
}

template<class T, uint x>
inline swizz<T, x>::operator T() const
{
	return *(T*)(this + x);
}

template<class T, uint x, uint y>
inline swizz<T, x, y>& swizz<T, x, y>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	return *this;
}

template<class T, uint x, uint y>
template<uint a, uint b>
inline swizz<T, x, y>& swizz<T, x, y>::operator=(const swizz<T, a, b>& v)
{
	if (this == &v) return operator=(vec2(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	return *this;
}

template<class T, uint x, uint y, uint z>
inline swizz<T, x, y, z>& swizz<T, x, y, z>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	*(T*)(this + z) = *(&v + z);
	return *this;
}

template<class T, uint x, uint y, uint z>
template<uint a, uint b, uint c>
inline swizz<T, x, y, z>& swizz<T, x, y, z>::operator=(const swizz<T, a, b, c>& v)
{
	if (this == &v) return operator=(vec3(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	*(T*)(this + z) = *(&v + c);
	return *this;
}

template<class T, uint x, uint y, uint z, uint w>
inline swizz<T, x, y, z, w>& swizz<T, x, y, z, w>::operator=(const swizz& v)
{
	*(T*)(this + x) = *(&v + x);
	*(T*)(this + y) = *(&v + y);
	*(T*)(this + z) = *(&v + z);
	*(T*)(this + w) = *(&v + w);
	return *this;
}

template<class T, uint x, uint y, uint z, uint w>
template<uint a, uint b, uint c, uint d>
inline swizz<T, x, y, z, w>& swizz<T, x, y, z, w>::operator=(const swizz<T, a, b, c, d>& v)
{
	if (this == &v) return operator=(vec4(v));
	*(T*)(this + x) = *(&v + a);
	*(T*)(this + y) = *(&v + b);
	*(T*)(this + z) = *(&v + c);
	*(T*)(this + w) = *(&v + d);
	return *this;
}
