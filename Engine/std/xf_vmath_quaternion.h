#pragma once
#include "xf_vmath_mat.h"

template<class T>
struct quaternion {
	union {
		T data[4];
		struct { T x, y, z, w; };
		struct { T i, j, k, s; };
		vec<T, 3> v;
		vec<T, 4> q;
	};
	template<uint a, uint b, uint c>
	quaternion(const base<T, a, b, c>& v, T w);
	quaternion();
	quaternion(T x, T y, T z, T w);
	quaternion(const vec<T, 3>& v, T w);
	quaternion(const quaternion& q);
	quaternion(const matrix3<T>&);
	quaternion(const matrix4<T>&);
	T len() const;
	T len2() const;
	quaternion& normalize();
	quaternion& operator=(const quaternion& q);
	quaternion  operator ~() const;
	quaternion  operator -() const;
	quaternion& operator += (const quaternion& q);
	quaternion& operator -= (const quaternion& q);
	quaternion  operator +  (const quaternion& q) const;
	quaternion  operator -  (const quaternion& q) const;
	quaternion& operator *= (T s);
	quaternion& operator /= (T s);
	quaternion  operator *  (float s) const;
	quaternion  operator /  (float s) const;
	quaternion  operator /  (const quaternion& q) const;
	quaternion  operator *= (const quaternion& q);
	quaternion  operator /= (const quaternion& q);
	quaternion  operator * (const quaternion& q) const;
	operator matrix3<T>() const;
	operator matrix4<T>() const;
	template<uint x, uint y, uint z>
	vec<T, 3> operator * (const base<T, x, y, z>& v) const;
};


template<class T, uint x, uint y, uint z>
vec<T, 3> operator * (const base<T, x, y, z>& v, const quaternion<T>& q);
quaternion<float> axang(float x, float y, float z, float w);
template<class T, uint x, uint y, uint z>
quaternion<T> axang(const base<T, x, y, z>& v, T w);

template<class T>
T dot(const quaternion<T>& l, const quaternion<T>& r);

template<class T>
inline std::ostream& operator << (std::ostream& s, const quaternion<T>& q)
{
	return s << q.q;
}

template<class T>
inline T dot(const quaternion<T>& l, const quaternion<T>& r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}

template<class T, uint x, uint y, uint z>
inline vec<T, 3> operator * (const base<T, x, y, z>& v, const quaternion<T>& q) {
	T _x = *(T*)(&v + y) * q.k - *(T*)(&v + z) * q.j + *(T*)(&v + x) * q.s;
	T _y = *(T*)(&v + z) * q.i - *(T*)(&v + x) * q.k + *(T*)(&v + y) * q.s;
	T _z = *(T*)(&v + x) * q.j - *(T*)(&v + y) * q.i + *(T*)(&v + z) * q.s;
	T _w = *(T*)(&v + x) * q.i + *(T*)(&v + y) * q.j + *(T*)(&v + z) * q.k;
	return
	{
		_y * q.k - _z * q.j + _x * q.s + q.i * _w,
		_z * q.i - _x * q.k + _y * q.s + q.j * _w,
		_x * q.j - _y * q.i + _z * q.s + q.k * _w
	};
}

template<class T>
template <uint a, uint b, uint c>
inline quaternion<T>::quaternion(const base<T, a, b, c>& v, T w)
	: data{ *(T*)(&v + a), *(T*)(&v + b), *(T*)(&v + c), w }
{
}

template<class T>
inline quaternion<T>::quaternion()
	: data{ 0, 0, 0, 1 }
{
}

template<class T>
inline quaternion<T>::quaternion(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline quaternion<T>::quaternion(const vec<T, 3>& v, T w)
	: data{ v.x, v.y, v.z, w }
{
}

template<class T>
inline quaternion<T>::quaternion(const quaternion<T>& q)
	: data{ q.x, q.y, q.z, q.w }
{
}

template<class T>
inline quaternion<T>::quaternion(const matrix3<T>& m)
{
	float tr = m(0, 0) + m(1, 1) + m(2, 2);
	if (tr > 0.f) {
		float S = 0.5f / sqrt(tr + 1.f);
		w = 0.25f / S;
		x = (m(2, 1) - m(1, 2)) * S;
		y = (m(0, 2) - m(2, 0)) * S;
		z = (m(1, 0) - m(0, 1)) * S;
	}
	else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(0, 0) - m(1, 1) - m(2, 2));
		w = (m(2, 1) - m(1, 2)) * S;
		x = 0.25f / S;
		y = (m(0, 1) + m(1, 0)) * S;
		z = (m(0, 2) + m(2, 0)) * S;
	}
	else if (m(1, 1) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(1, 1) - m(0, 0) - m(2, 2));
		w = (m(0, 2) - m(2, 0)) * S;
		x = (m(0, 1) + m(1, 0)) * S;
		y = 0.25f / S;
		z = (m(1, 2) + m(2, 1)) * S;
	}
	else {
		float S = 0.5f / sqrt(1.f + m(2, 2) - m(0, 0) - m(1, 1));
		w = (m(1, 0) - m(0, 1)) * S;
		x = (m(0, 2) + m(2, 0)) * S;
		y = (m(1, 2) + m(2, 1)) * S;
		z = 0.25f / S;
	}
}

template<class T>
inline quaternion<T>::quaternion(const matrix4<T>& m)
{
	float tr = m(0, 0) + m(1, 1) + m(2, 2);
	if (tr > 0.f) {
		float S = 0.5f / sqrt(tr + 1.f);
		w = 0.25f / S;
		x = (m(2, 1) - m(1, 2)) * S;
		y = (m(0, 2) - m(2, 0)) * S;
		z = (m(1, 0) - m(0, 1)) * S;
	}
	else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(0, 0) - m(1, 1) - m(2, 2));
		w = (m(2, 1) - m(1, 2)) * S;
		x = 0.25f / S;
		y = (m(0, 1) + m(1, 0)) * S;
		z = (m(0, 2) + m(2, 0)) * S;
	}
	else if (m(1, 1) > m(2, 2)) {
		float S = 0.5f / sqrt(1.f + m(1, 1) - m(0, 0) - m(2, 2));
		w = (m(0, 2) - m(2, 0)) * S;
		x = (m(0, 1) + m(1, 0)) * S;
		y = 0.25f / S;
		z = (m(1, 2) + m(2, 1)) * S;
	}
	else {
		float S = 0.5f / sqrt(1.f + m(2, 2) - m(0, 0) - m(1, 1));
		w = (m(1, 0) - m(0, 1)) * S;
		x = (m(0, 2) + m(2, 0)) * S;
		y = (m(1, 2) + m(2, 1)) * S;
		z = 0.25f / S;
	}
}

template<class T>
inline T quaternion<T>::len() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

template<class T>
inline T quaternion<T>::len2() const
{
	return x * x + y * y + z * z + w * w;
}

template<class T>
inline quaternion<T>& quaternion<T>::normalize()
{
	~q;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator=(const quaternion<T>& q)
{
	x = q.x, y = q.y, z = q.z, w = q.w;
	return *this;
}

template<class T>
inline quaternion<T> quaternion<T>::operator~() const
{
	return { -x, -y, -z, w };
}

template<class T>
inline quaternion<T> quaternion<T>::operator-() const
{
	return { -x, -y, -z, -w };
}

template<class T>
inline quaternion<T>& quaternion<T>::operator+=(const quaternion<T>& q)
{
	x += q.x, y += q.y, z += q.z, w += q.w;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator-=(const quaternion<T>& q)
{
	x -= q.x, y -= q.y, z -= q.z, w -= q.w;
	return *this;
}

template<class T>
inline quaternion<T> quaternion<T>::operator+(const quaternion<T>& q) const
{
	return quaternion<T>(*this) += q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator-(const quaternion<T>& q) const
{
	return quaternion<T>(*this) -= q;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator*=(T s)
{
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

template<class T>
inline quaternion<T>& quaternion<T>::operator/=(T s)
{
	s = 1 / s;
	x *= s, y *= s, z *= s, w *= s;
	return *this;
}

template<class T>
inline quaternion<T>  quaternion<T>::operator*(float s) const
{
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T>  quaternion<T>::operator/(float s) const
{
	s = 1 / s;
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T> operator*(float s, const quaternion<T>& q)
{
	return { q.x * s, q.y * s, q.z * s, q.w * s };
}

template<class T>
inline quaternion<T> operator/(float s, const quaternion<T>& q)
{
	s /= q.len2();
	return ~q *= s;
}

template<class T>
inline quaternion<T> quaternion<T>::operator/(const quaternion<T>& q) const
{
	return (*this * ~q) /= q.len2();
}

template<class T>
inline quaternion<T> quaternion<T>::operator*=(const quaternion<T>& q)
{
	return *this = *this * q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator/=(const quaternion<T>& q)
{
	return *this = *this / q;
}

template<class T>
inline quaternion<T> quaternion<T>::operator*(const quaternion<T>& q) const
{
	return 
	{ 
		s * q.i + i * q.s + j * q.k - k * q.j, 
		s * q.j + j * q.s + k * q.i - i * q.k,
		s * q.k + k * q.s + i * q.j - j * q.i, 
		s * q.s - i * q.i - j * q.j - k * q.k 
	};
}

template<class T>
inline quaternion<T>::operator matrix3<T>() const
{
	T i2 = i + i, j2 = j + j, k2 = k + k;
	T ii = i * i2, ij = i * j2, ik = i * k2;
	T jj = j * j2, jk = j * k2, kk = k * k2;
	T si = s * i2, sj = s * j2, sk = s * k2;
	return 
	{ 
		1 - (jj + kk), ij - sk, ik + sj, 
		ij + sk, 1 - (ii + kk), jk - si, 
		ik - sj, jk + si, 1 - (ii + jj) 
	};
}

template<class T>
inline quaternion<T>::operator matrix4<T>() const
{
	T i2 = i + i, j2 = j + j, k2 = k + k;
	T ii = i * i2, ij = i * j2, ik = i * k2;
	T jj = j * j2, jk = j * k2, kk = k * k2;
	T si = s * i2, sj = s * j2, sk = s * k2;
	return 
	{ 
		1 - (jj + kk), ij - sk, ik + sj, 0, 
		ij + sk, 1 - (ii + kk), jk - si, 0, 
		ik - sj, jk + si, 1 - (ii + jj), 
		0, 0, 0, 0, 1 
	};
}

template<class T>
template<uint a, uint b, uint c>
inline vec<T, 3> quaternion<T>::operator *(const base<T, a, b, c>& v) const
{
	T _x = j * *(T*)(&v + c) - k * *(T*)(&v + b) + s * *(T*)(&v + a);
	T _y = k * *(T*)(&v + a) - i * *(T*)(&v + c) + s * *(T*)(&v + b);
	T _z = i * *(T*)(&v + b) - j * *(T*)(&v + a) + s * *(T*)(&v + c);
	T _w = i * *(T*)(&v + a) + j * *(T*)(&v + b) + k * *(T*)(&v + c);
	return 
	{ 
		j * _z - k * _y + s * _x + i * _w, 
		k * _x - i * _z + s * _y + j * _w,
		i * _y - j * _x + s * _z + k * _w 
	};
}


inline quaternion<float> axang(float x, float y, float z, float w)
{
	float l = 1 / sqrtf(x * x + y * y + z * z) * sinf(w *= 0.5f);
	return { x * l, y * l, z * l, cosf(w) };
}

template<class T, uint x, uint y, uint z>
inline quaternion<T> axang(const base<T, x, y, z>& v, T w)
{
	T l = 1 / v.len() * sinf(w *= 0.5f);
	return { v[x] * l, v[y] * l, v[z] * l , cosf(w) };
}

using quat = quaternion<float>;
