#pragma once
#include "xf_mathf.h"
#include "xf_str.h"

template<class T, uint...> struct base;
template<class T, uint...> struct swizz;
template<class T, uint> struct vec;

using  vec2 = vec<float, 2>;
using ivec2 = vec<int, 2>;
using uvec2 = vec<uint, 2>;
using  vec3 = vec<float, 3>;
using ivec3 = vec<int, 3>;
using uvec3 = vec<uint, 3>;
using  vec4 = vec<float, 4>;
using ivec4 = vec<int, 4>;
using uvec4 = vec<uint, 4>;

template<template<class, uint...> class V, class T, uint h, uint... t>
struct type_proxy : type_proxy<V, T, h - 1, h - 1, t...>
{
};

template<template<class, uint...> class V, class T, uint...t>
struct type_proxy <V, T, 0, t...>
{
	using type = V<T, t...>;

	template<uint n>
	struct mul
	{
		using type = V<T, n * t...>;
	};
};

template<class T, uint n>
using dvec = typename type_proxy<swizz, T, n>::template mul<n + 1>::type;
template<class T, uint n>
using cvec = typename type_proxy<swizz, T, n>::template mul<n>::type;

using cvec2 = cvec<float, 2>;
using cvec3 = cvec<float, 3>;
using cvec4 = cvec<float, 4>;
using dvec2 = dvec<float, 2>;
using dvec3 = dvec<float, 3>;
using dvec4 = dvec<float, 4>;

template<class T, uint...x>
std::ostream& operator << (std::ostream&, const base<T, x...>& v);
template<class T, uint...x>
xfstr tostr(const base<T, x...>& v);
template<class T, uint...x, uint...y>
T dot(const base<T, x...>& l, const base<T, y...>& r);
template<class T, uint x, uint y, uint z, uint x1, uint y1, uint z1>
vec<T, 3> cross(const base<T, x, y, z>& l, const base<T, x1, y1, z1>& r);
template<class T>
vec<T, 3> perp(const vec<T, 3>& v);
template<class T>
vec<T, 2> norm(T x, T y);
template<class T>
vec<T, 3> norm(T x, T y, T z);
template<class T>
vec<T, 4> norm(T x, T y, T z, T w);

template<class T, uint...x>
struct alignas(sizeof(T)) base
{
	operator vec<T, sizeof...(x)>() const;
	swizz<T, x...>& operator = (const base & v);
	template<uint ...y>	swizz<T, x...>& operator =  (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator += (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator -= (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator *= (const base<T, y...> & v);
	template<uint ...y>	swizz<T, x...>& operator /= (const base<T, y...> & v);

	template<uint ...y>	vec<T, sizeof...(x)> operator + (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator - (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator * (const base<T, y...> & v) const;
	template<uint ...y>	vec<T, sizeof...(x)> operator / (const base<T, y...> & v) const;

	swizz<T, x...>& operator =  (T n);
	swizz<T, x...>& operator += (T n);
	swizz<T, x...>& operator -= (T n);
	swizz<T, x...>& operator *= (T n);
	swizz<T, x...>& operator /= (T n);

	vec<T, sizeof...(x)> operator + (T n) const;
	vec<T, sizeof...(x)> operator - (T n) const;
	vec<T, sizeof...(x)> operator * (T n) const;
	vec<T, sizeof...(x)> operator / (T n) const;

	vec<T, sizeof...(x)> norm() const;
	vec<T, sizeof...(x)> operator -() const;
	swizz<T, x...>& operator ~();

	template<uint ...y>
	T operator ^ (const base<T, y...> & v) const;
	template<uint ...y>
	vec<T, sizeof...(x)> operator % (const base<T, y...> & v) const;
	T len() const;
	T len2() const;
	T operator !() const;
	template<uint ...y>
	bool operator == (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator != (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator < (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator <= (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator > (const base<T, y...> & v) const;
	template<uint ...y>
	bool operator >= (const base<T, y...> & v) const;

	T& operator [](uint n) const;
};


template<class T, uint ...x>
inline base<T, x...>::operator vec<T, sizeof...(x)>() const
{
	return { *(T*)(this + x)... };
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator=(const base& v)
{
	((*(T*)(this + x) = *(T*)(&v + x)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) = *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator+=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator+=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) += *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator-=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator-=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) -= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator*=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator*=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) *= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline swizz<T, x...>& base<T, x...>::operator/=(const base<T, y...>& v)
{
	if ((T*)this == (T*)&v) return operator/=(vec<T, sizeof...(y)>(v));
	((*(T*)(this + x) /= *(T*)(&v + y)), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator+(const base<T, y...>& v) const
{
	return { *(T*)(this + x) + *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator-(const base<T, y...>& v) const
{
	return { *(T*)(this + x) - *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator*(const base<T, y...>& v) const
{
	return { *(T*)(this + x) * *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator/(const base<T, y...>& v) const
{
	return { *(T*)(this + x) / *(T*)(&v + y)... };
}

template<class T, uint ...x>
template<uint ...y>
inline T base<T, x...>::operator^(const base<T, y...>& v) const
{
	return acosf(((*(T*)(this + x) * *(T*)(&v + y)) + ...)
		/ sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...))
		/ sqrt(((*(T*)(&v + y) * *(T*)(&v + y)) + ...)));
}

template<class T, uint ...x>
template<uint ...y>
inline vec<T, sizeof...(x)> base<T, x...>::operator%(const base<T, y...>& v) const
{
	return ~operator-(v);
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator=(T n)
{
	((*(T*)(this + x) = n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator+=(T n)
{
	((*(T*)(this + x) += n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator-=(T n)
{
	((*(T*)(this + x) -= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator*=(T n)
{
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator/=(T n)
{
	n = 1 / n;
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator+(T n) const
{
	return { *(T*)(this + x) + n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator-(T n) const
{
	return { *(T*)(this + x) - n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator*(T n) const
{
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator/(T n) const
{
	n = 1 / n;
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::norm() const
{
	T n = 1 / sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
	return { *(T*)(this + x) * n... };
}

template<class T, uint ...x>
inline vec<T, sizeof...(x)> base<T, x...>::operator-() const
{
	return { -*(T*)(this + x)... };
}

template<class T, uint ...x>
inline swizz<T, x...>& base<T, x...>::operator~()
{
	T n = 1 / sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
	((*(T*)(this + x) *= n), ...);
	return *(swizz<T, x...>*)this;
}

template<class T, uint ...x>
inline T base<T, x...>::len() const
{
	return sqrt(((*(T*)(this + x) * *(T*)(this + x)) + ...));
}

template<class T, uint ...x>
inline T base<T, x...>::len2() const
{
	return ((*(T*)(this + x) * *(T*)(this + x)) + ...);
}

template<class T, uint ...x>
inline T base<T, x...>::operator!() const
{
	return ((*(T*)(this + x) * *(T*)(this + x)) + ...);
}

template<class T, uint ...x>
inline T& base<T, x...>::operator[](uint n) const
{
	return *(T*)(this + n);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator==(const base<T, y...>& v) const
{
	return ((is0(*(T*)(this + x) - *(T*)(&v + y))) && ...);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator!=(const base<T, y...>& v) const
{
	return !((is0(*(T*)(this + x) - *(T*)(&v + y))) && ...);
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator<(const base<T, y...>& v) const
{
	vec<T, sizeof...(x)> u = { *(T*)(this + x) - *(T*)(&v + y)... };
	return is0(u.x) ? u.y < 0 : u.x < 0;
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator<=(const base<T, y...>& v) const
{
	return operator<(v) || operator ==(v);
}


template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator>(const base<T, y...>& v) const
{
	vec<T, sizeof...(x)> u = { *(T*)(this + x) - *(T*)(&v + y)... };
	return is0(u.x) ? u.y > 0 : u.x > 0;
}

template<class T, uint ...x>
template<uint ...y>
inline bool base<T, x...>::operator>=(const base<T, y...>& v) const
{
	return operator>(v) || operator ==(v);
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator+(T n, const base<T, x...>& v)
{
	return { n + *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator-(T n, const base<T, x...>& v)
{
	return { n - *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator*(T n, const base<T, x...>& v)
{
	return { n * *(T*)(&v + x)... };
}

template<class T, uint...x>
inline vec<T, sizeof...(x)> operator/(T n, const base<T, x...>& v)
{
	return { n / *(T*)(&v + x)... };
}

template<class T, uint...x>
inline std::ostream& operator<<(std::ostream& s, const base<T, x...>& v)
{
	((s << *(T*)(&v + x) << ' '), ...);
	return s << '\n';
}

template<class T, uint...x, uint...y>
inline T dot(const base<T, x...>& l, const base<T, y...>& r)
{
	return ((*(T*)(&l + x) * *(T*)(&r + y)) + ...);
}

template<class T, uint x, uint y, uint z, uint x1, uint y1, uint z1>
inline vec<T, 3> cross(const base<T, x, y, z>& l, const base<T, x1, y1, z1>& r)
{
	return
	{
		*(T*)(&l + y) * *(T*)(&r + z1) - *(T*)(&l + z) * *(T*)(&r + y1),
		*(T*)(&l + z) * *(T*)(&r + x1) - *(T*)(&l + x) * *(T*)(&r + z1),
		*(T*)(&l + x) * *(T*)(&r + y1) - *(T*)(&l + y) * *(T*)(&r + x1)
	};
}

template<class T, uint...x>
inline xfstr tostr(const base<T, x...>& v)
{
	xfstr re;
	((re += tostr(*(T*)(&v + x)) + ' '), ...);
	return re;
}


template<class T>
inline vec<T, 3> perp(const vec<T, 3>& v)
{
	uint c = !is0(v.x) + !is0(v.y) * 2 + !is0(v.z) * 4;
	switch (c) {
	case 1: return { 0, 1, 0 }; //x
	case 2: return { 0, 0, 1 }; //y
	case 4: return { 1, 0, 0 }; //z
	case 3: return { -v.y, v.x,  0 }; //xy
	case 5: return { v.z, 0, -v.x };  //xz
	case 6: return { 0, -v.z, v.y };  //yz
	case 7: return { -v.y * v.z, v.x * v.z, 0 }; //xyz
	default: return {};
	}
}

template<class T>
inline vec<T, 2> norm(T x, T y)
{
	T n = 1 / sqrt(x * x + y * y);
	return { x * n , y * n };
}

template<class T>
inline vec<T, 3> norm(T x, T y, T z)
{
	T n = 1 / sqrt(x * x + y * y + z * z);
	return { x * n , y * n, z * n };
}

template<class T>
inline vec<T, 4> norm(T x, T y, T z, T w)
{
	T n = 1 / sqrt(x * x + y * y + z * z + w * w);
	return { x * n , y * n, z * n, w * n };
}
