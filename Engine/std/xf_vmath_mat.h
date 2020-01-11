#pragma once
#include "xf_vmath_vec.h"

template<class T>
struct matrix2 {
	template<uint x, uint y, uint x1, uint y1>
	matrix2(const base<T, x, y>& a, const base<T, x1, y1>& b);
	matrix2();
	matrix2(T x);
	matrix2(T x, T y, T z, T w);
	matrix2(const matrix2& m);
	matrix2& operator = (const matrix2& m);
	union {
		T data[4];
		vec<T, 2> row[2];
		cvec<T, 2> col[2];
		dvec<T, 2> diag;
	};
	T det() const;
	matrix2 inv() const;
	matrix2 xpos() const;
	matrix2 operator *(const matrix2& r) const;
	template<uint x, uint y>
	vec<T, 2> operator *(const base<T, x, y>& v) const;
	matrix2& operator *=	(T s);
	matrix2& operator /=	(T s);
	matrix2  operator *	(T s) const;
	matrix2  operator /	(T s) const;
};
template<class T>
struct matrix4;

template<class T>
struct matrix3 {
	template<
		uint  x, uint  y, uint z,
		uint x1, uint y1, uint z1,
		uint x2, uint y2, uint z2>
		matrix3(const base<T, x, y, z>& a, const base<T, x1, y1, z1>& b, const base<T, x2, y2, z2>& c);
	matrix3();
	matrix3(T x);
	matrix3(T  x, T  y, T z, T x1, T y1, T z1, T x2, T y2, T z2);
	matrix3(const matrix3& m);

	matrix3& operator = (const matrix3& m);
	union {
		T data[9];
		vec<T, 3>  row[3];
		cvec<T, 3> col[3];
		dvec<T, 3> diag;
	};
	T det() const;
	matrix3 inv() const;
	matrix3 xpos() const;
	matrix3 operator * (const matrix3& r) const;
	template<uint x, uint y, uint z>
	vec<T, 3> operator *(const base<T, x, y, z>& v) const;
	T& operator()(uint r, uint c);
	T  operator()(uint r, uint c) const;
	matrix3& operator *=(T s);
	matrix3 operator *		(T s) const;
	matrix3& operator /=	(T s);
	matrix3 operator /		(T s) const;
	operator matrix4<T>() const;
};

template<class T>
struct matrix4 {
	template<
		uint  x, uint  y, uint  z, uint  w,
		uint x1, uint y1, uint z1, uint w1,
		uint x2, uint y2, uint z2, uint w2,
		uint x3, uint y3, uint z3, uint w3>
		matrix4(const base<T, x, y, z, w>& a,
			const base<T, x1, y1, z1, w1>& b,
			const base<T, x2, y2, z2, w2>& c,
			const base<T, x3, y3, z3, w3>& d);
	matrix4();
	matrix4(T x);
	matrix4(T  x, T  y, T  z, T w,
		T x1, T y1, T z1, T w1,
		T x2, T y2, T z2, T w2,
		T x3, T y3, T z3, T w3);
	matrix4(const matrix4& m);
	matrix4& operator = (const matrix4& m);

	union {
		T data[16];
		vec<T, 4>  row[4];
		cvec<T, 4> col[4];
		dvec<T, 4> diag;
	};
	T det() const;
	matrix4 inv() const;
	matrix4 xpos() const;
	matrix4 operator *(const matrix4& r) const;
	template<uint x, uint y, uint z>
	vec<T, 3> operator *(const base<T, x, y, z>& v) const;
	template<uint x, uint y, uint z, uint w>
	vec<T, 4> operator *(const base<T, x, y, z, w>& v) const;
	T& operator()(uint r, uint c);
	T  operator()(uint r, uint c) const;
	matrix4& operator *= (T s);
	matrix4& operator /=	(T s);
	matrix4 operator *		(T s) const;
	matrix4 operator /		(T s) const;
	operator matrix3<T>() const;
};

template<class T>
matrix3<T> rotx(T angle);
template<class T>
matrix3<T> roty(T angle);
template<class T>
matrix3<T> rotz(T angle);

template<class T>
std::ostream& operator << (std::ostream&, const matrix2<T>&);
template<class T>
std::ostream& operator << (std::ostream&, const matrix3<T>&);
template<class T>
std::ostream& operator << (std::ostream&, const matrix4<T>&);

matrix4<float> perspective(float fov, float aspect, float n, float f);
matrix4<float> ortho(float l, float r, float b, float t);
matrix4<float> ortho(float l, float r, float b, float t, float n, float f);
matrix4<float> view(const vec<float, 3>& p, const vec<float, 3>& r, const vec<float, 3>& u, const vec<float, 3>& d);


template<class T, uint x, uint y>
vec<T, 2> operator *(const base<T, x, y>& v, const matrix2<T>& m);
template<class T, uint x, uint y, uint z>
vec<T, 3> operator *(const base<T, x, y, z>& v, const matrix3<T>& m);
template<class T, uint x, uint y, uint z, uint w>
vec<T, 4> operator *(const base<T, x, y, z, w>& v, const matrix4<T>& m);


template<class T>
template<uint x, uint y, uint x1, uint y1>
inline matrix2<T>::matrix2(const base<T, x, y>& a, const base<T, x1, y1>& b)
	: data
{
	*(T*)(&a + x), *(T*)(&a + x1),
	*(T*)(&b + y), *(T*)(&b + y1)
}
{
}

template<class T>
inline matrix2<T>::matrix2()
	: data{ 1, 0, 0, 1 }
{
}

template<class T>
inline matrix2<T>::matrix2(T x)
	: data{ x, 0, 0, x }
{
}

template<class T>
inline matrix2<T>::matrix2(T x, T y, T z, T w)
	: data{ x, y, z, w }
{
}

template<class T>
inline matrix2<T>::matrix2(const matrix2& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3] }
{
}


template<class T>
inline matrix2<T>& matrix2<T>::operator=(const matrix2& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	return *this;
}

template<class T>
inline T matrix2<T>::det() const
{
	return data[0] * data[3] - data[1] * data[2];
}

template<class T>
inline matrix2<T> matrix2<T>::inv() const
{
	T det = 1 / (data[0] * data[3] - data[1] * data[2]);
	return { det * data[3], -det * data[1], -det * data[2], det * data[0] };
}

template<class T>
inline matrix2<T> matrix2<T>::xpos() const
{
	return { data[0], data[2], data[1], data[3] };
}

template<class T>
inline matrix2<T> matrix2<T>::operator*(const matrix2& r) const
{
	return {
		data[0] * r.data[0] + data[1] * r.data[2],
		data[0] * r.data[1] + data[1] * r.data[3],
		data[2] * r.data[0] + data[3] * r.data[2],
		data[2] * r.data[1] + data[3] * r.data[3],
	};
}

template<class T>
template <uint x, uint y>
inline vec<T, 2> matrix2<T>::operator*(const base<T, x, y>& v) const
{
	return {
		*(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1],
		*(T*)(&v + x) * data[2] + *(T*)(&v + y) * data[3],
	};
}

template<class T>
inline matrix2<T>& matrix2<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	return *this;
}

template<class T>
inline matrix2<T>& matrix2<T>::operator/=(T s)
{
	return operator*=(1 / s);
}

template<class T>
inline matrix2<T> matrix2<T>::operator*(T s) const
{
	return matrix2(*this) *= s;
}

template<class T>
inline matrix2<T> matrix2<T>::operator/(T s) const
{
	return matrix2(*this) *= (1 / s);
}


template<class T>
template <uint x, uint y, uint z, uint x1, uint y1, uint z1, uint x2, uint y2, uint z2>
inline matrix3<T>::matrix3(const base<T, x, y, z>& a, const base<T, x1, y1, z1>& b, const base<T, x2, y2, z2>& c)
	: data{ *(T*)(&a + x), *(T*)(&a + y), *(T*)(&a + z), *(T*)(&b + x1), *(T*)(&b + y1),
		*(T*)(&b + z1), *(T*)(&c + x2), *(T*)(&c + y2), *(T*)(&c + z2) }
{
}

template<class T>
inline  matrix3<T>::matrix3()
	: data{ 1, 0, 0, 0, 1, 0, 0, 0, 1 }
{
}

template<class T>
inline  matrix3<T>::matrix3(T x)
	: data{ x, 0, 0, 0, x, 0, 0, 0, x }
{
}

template<class T>
inline  matrix3<T>::matrix3(T x, T y, T z, T x1, T y1, T z1, T x2, T y2, T z2)
	: data{ x, y, z, x1, y1, z1, x2, y2, z2 }
{
}

template<class T>
inline  matrix3<T>::matrix3(const matrix3<T>& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5],
		m.data[6], m.data[7], m.data[8] }
{
}

template<class T>
inline  matrix3<T>& matrix3<T>::operator=(const matrix3<T>& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	return *this;
}

template<class T>
inline T matrix3<T>::det() const
{
	return data[0] * (data[4] * data[8] - data[5] * data[7])
		+ data[1] * (data[5] * data[6] - data[3] * data[8])
		+ data[2] * (data[3] * data[7] - data[4] * data[6]);
}

template<class T>
inline matrix3<T> matrix3<T>::inv() const
{
	T a = data[4] * data[8] - data[5] * data[7]; 
	T b = data[5] * data[6] - data[3] * data[8];
	T c = data[3] * data[7] - data[4] * data[6];
	T det = 1 / (data[0] * a + data[1] * b + data[2] * c);
	return
	{
		det * a, det * (data[2] * data[7] - data[1] * data[8]), det * (data[1] * data[5] - data[2] * data[4]),
		det * b, det * (data[0] * data[8] - data[2] * data[6]), det * (data[2] * data[3] - data[0] * data[5]),
		det * c, det * (data[1] * data[6] - data[0] * data[7]), det * (data[0] * data[4] - data[1] * data[3])
	};
}

template<class T>
inline matrix3<T> matrix3<T>::xpos() const
{
	return { data[0], data[3], data[6], data[1], data[4], data[7], data[2],
		data[5], data[8] };
}

template<class T>
inline matrix3<T> matrix3<T>::operator*(const matrix3<T>& r) const
{
	return {
		data[0] * r.data[0] + data[1] * r.data[3] + data[2] * r.data[6],
		data[0] * r.data[1] + data[1] * r.data[4] + data[2] * r.data[7],
		data[0] * r.data[2] + data[1] * r.data[5] + data[2] * r.data[8],

		data[3] * r.data[0] + data[4] * r.data[3] + data[5] * r.data[6],
		data[3] * r.data[1] + data[4] * r.data[4] + data[5] * r.data[7],
		data[3] * r.data[2] + data[4] * r.data[5] + data[5] * r.data[8],

		data[6] * r.data[0] + data[7] * r.data[3] + data[8] * r.data[6],
		data[6] * r.data[1] + data[7] * r.data[4] + data[8] * r.data[7],
		data[6] * r.data[2] + data[7] * r.data[5] + data[8] * r.data[8],
	};
}

template<class T>
template <uint x, uint y, uint z>
inline vec<T, 3> matrix3<T>::operator*(const base<T, x, y, z>& v) const
{
	return {
		*(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1] + *(T*)(&v + z) * data[2],
		*(T*)(&v + x) * data[3] + *(T*)(&v + y) * data[4] + *(T*)(&v + z) * data[5],
		*(T*)(&v + x) * data[6] + *(T*)(&v + y) * data[7] + *(T*)(&v + z) * data[8],
	};
}

template<class T>
inline T& matrix3<T>::operator()(uint r, uint c)
{
	return *(data + 3 * r + c);
}

template<class T>
inline T matrix3<T>::operator()(uint r, uint c) const
{
	return *(data + 3 * r + c);
}

template<class T>
inline matrix3<T>& matrix3<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	return *this;
}

template<class T>
inline matrix3<T> matrix3<T>::operator*(T s) const
{
	return matrix3<T>(*this) *= s;
}

template<class T>
inline matrix3<T>& matrix3<T>::operator/=(T s)
{
	return operator*=(1 / s);
}

template<class T>
inline matrix3<T> matrix3<T>::operator/(T s) const
{
	return matrix3<T>(*this) *= (1 / s);
}

template<class T>
inline matrix3<T>::operator matrix4<T>() const
{
	return
	{
		row[0].x, row[0].y, row[0].z, 0,
		row[1].x, row[1].y, row[1].z, 0,
		row[2].x, row[2].y, row[2].z, 0,
		0, 0, 0, 1,
	};
}


template<class T>
template <uint x, uint y, uint z, uint w, uint x1, uint y1, uint z1, uint w1, uint x2, uint y2, uint z2,
	uint w2, uint x3, uint y3, uint z3, uint w3>
	inline matrix4<T>::matrix4(const base<T, x, y, z, w>& a, const base<T, x1, y1, z1, w1>& b,
		const base<T, x2, y2, z2, w2>& c, const base<T, x3, y3, z3, w3>& d)
	: data
{
		*(T*)(&a + x), *(T*)(&a + y), *(T*)(&a + z), *(T*)(&a + w),
		*(T*)(&b + x1), *(T*)(&b + y1), *(T*)(&b + z1), *(T*)(&b + w1),
		*(T*)(&c + x2), *(T*)(&c + y2), *(T*)(&c + z2), *(T*)(&c + w2),
		*(T*)(&d + x3), *(T*)(&d + y3), *(T*)(&d + z3), *(T*)(&d + w3),
}
{
}

template<class T>
inline matrix4<T>::matrix4()
	: data{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
{
}
template<class T>
inline matrix4<T>::matrix4(T x)
	: data{ x, 0, 0, 0, 0, x, 0, 0, 0, 0, x, 0, 0, 0, 0, 1 }
{
}

template<class T>
inline matrix4<T>::matrix4(
	T x, T y, T z, T w, T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3)
	: data{ x, y, z, w, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3 }
{
}

template<class T>
inline matrix4<T>::matrix4(const matrix4<T>& m)
	: data{ m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5],
		m.data[6], m.data[7], m.data[8], m.data[9], m.data[10], m.data[11],
		m.data[12], m.data[13], m.data[14], m.data[15] }
{
}

template<class T>
inline matrix4<T>& matrix4<T>::operator=(const matrix4<T>& m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	data[9] = m.data[9];
	data[10] = m.data[10];
	data[11] = m.data[11];
	data[12] = m.data[12];
	data[13] = m.data[13];
	data[14] = m.data[14];
	data[15] = m.data[15];
	return *this;
}

template<class T>
inline T matrix4<T>::det() const
{
	T det_08_09 = (data[8] * data[13] - data[9] * data[12]);
	T det_08_10 = (data[8] * data[14] - data[10] * data[12]);
	T det_08_11 = (data[8] * data[15] - data[11] * data[12]);
	T det_09_10 = (data[9] * data[14] - data[10] * data[13]);
	T det_09_11 = (data[9] * data[15] - data[11] * data[13]);
	T det_10_11 = (data[10] * data[15] - data[11] * data[14]);
	return data[0]
		* (data[5] * (det_10_11)-data[6] * (det_09_11)+data[7] * (det_09_10))
		- data[1]
		* (data[4] * (det_10_11)-data[6] * (det_08_11)+data[7] * (det_08_10))
		+ data[2]
		* (data[4] * (det_09_11)-data[5] * (det_08_11)+data[7] * (det_08_09))
		- data[3]
		* (data[4] * (det_09_10)-data[5] * (det_08_10)+data[6] * (det_08_09));
}

template<class T>
inline matrix4<T> matrix4<T>::inv() const
{
	T zw0 = data[10] * data[15] - data[11] * data[14];
	T yw0 = data[9] * data[15] - data[11] * data[13];
	T yz0 = data[9] * data[14] - data[10] * data[13];
	T xw0 = data[8] * data[15] - data[11] * data[12];
	T xz0 = data[8] * data[14] - data[10] * data[12];
	T xy0 = data[8] * data[13] - data[9] * data[12];

	T zw1 = data[3] * data[14] - data[2] * data[15];
	T yw1 = data[3] * data[13] - data[1] * data[15];
	T yz1 = data[2] * data[13] - data[1] * data[14];
	T xw1 = data[3] * data[12] - *(data + 0) * data[15];
	T xz1 = data[2] * data[12] - *(data + 0) * data[14];
	T xy1 = data[1] * data[12] - *(data + 0) * data[13];

	T zw2 = data[2] * data[7] - data[3] * data[6];
	T yw2 = data[1] * data[7] - data[3] * data[5];
	T yz2 = data[1] * data[6] - data[2] * data[5];
	T xw2 = data[0] * data[7] - data[3] * data[4];
	T xz2 = data[0] * data[6] - data[2] * data[4];
	T xy2 = data[0] * data[5] - data[1] * data[4];

	T zw3 = data[11] * data[6] - data[10] * data[7];
	T yw3 = data[11] * data[5] - data[9] * data[7];
	T yz3 = data[10] * data[5] - data[9] * data[6];
	T xw3 = data[11] * data[4] - data[8] * data[7];
	T xz3 = data[10] * data[4] - data[8] * data[6];
	T xy3 = data[9] * data[4] - data[8] * data[5];

	T x0 = data[5] * zw0 - data[6] * yw0 + data[7] * yz0;
	T y0 = data[4] * zw0 - data[6] * xw0 + data[7] * xz0;
	T z0 = data[4] * yw0 - data[5] * xw0 + data[7] * xy0;
	T w0 = data[4] * yz0 - data[5] * xz0 + data[6] * xy0;

	T x1 = data[9] * zw1 - data[10] * yw1 + data[11] * yz1;
	T y1 = data[8] * zw1 - data[10] * xw1 + data[11] * xz1;
	T z1 = data[8] * yw1 - data[9] * xw1 + data[11] * xy1;
	T w1 = data[8] * yz1 - data[9] * xz1 + data[10] * xy1;

	T x2 = data[13] * zw2 - data[14] * yw2 + data[15] * yz2;
	T y2 = data[12] * zw2 - data[14] * xw2 + data[15] * xz2;
	T z2 = data[12] * yw2 - data[13] * xw2 + data[15] * xy2;
	T w2 = data[12] * yz2 - data[13] * xz2 + data[14] * xy2;

	T x3 = data[1] * zw3 - data[2] * yw3 + data[3] * yz3;
	T y3 = data[0] * zw3 - data[2] * xw3 + data[3] * xz3;
	T z3 = data[0] * yw3 - data[1] * xw3 + data[3] * xy3;
	T w3 = data[0] * yz3 - data[1] * xz3 + data[2] * xy3;

	T det = 1 / (data[0] * x0 - data[1] * y0 + data[2] * z0 - data[3] * w0);
	return { det * x0, det * -x1, det * x2, det * -x3, det * -y0, det * y1, det * -y2, det * y3,
		det * z0, det * -z1, det * z2, det * -z3, det * -w0, det * w1, det * -w2, det * w3 };
}

template<class T>
inline matrix4<T> matrix4<T>::xpos() const
{
	return { data[0], data[4], data[8], data[12], data[1], data[5], data[9],
		data[13], data[2], data[6], data[10], data[14], data[3],
		data[7], data[11], data[15] };
}

template<class T>
inline matrix4<T> matrix4<T>::operator*(const matrix4<T>& r) const
{
	return { data[0] * r.data[0] + data[1] * r.data[4] + data[2] * r.data[8]
			+ data[3] * r.data[12],
		data[0] * r.data[1] + data[1] * r.data[5] + data[2] * r.data[9]
			+ data[3] * r.data[13],
		data[0] * r.data[2] + data[1] * r.data[6] + data[2] * r.data[10]
			+ data[3] * r.data[14],
		data[0] * r.data[3] + data[1] * r.data[7] + data[2] * r.data[11]
			+ data[3] * r.data[15],

		data[4] * r.data[0] + data[5] * r.data[4] + data[6] * r.data[8]
			+ data[7] * r.data[12],
		data[4] * r.data[1] + data[5] * r.data[5] + data[6] * r.data[9]
			+ data[7] * r.data[13],
		data[4] * r.data[2] + data[5] * r.data[6] + data[6] * r.data[10]
			+ data[7] * r.data[14],
		data[4] * r.data[3] + data[5] * r.data[7] + data[6] * r.data[11]
			+ data[7] * r.data[15],

		data[8] * r.data[0] + data[9] * r.data[4] + data[10] * r.data[8]
			+ data[11] * r.data[12],
		data[8] * r.data[1] + data[9] * r.data[5] + data[10] * r.data[9]
			+ data[11] * r.data[13],
		data[8] * r.data[2] + data[9] * r.data[6] + data[10] * r.data[10]
			+ data[11] * r.data[14],
		data[8] * r.data[3] + data[9] * r.data[7] + data[10] * r.data[11]
			+ data[11] * r.data[15],

		data[12] * r.data[0] + data[13] * r.data[4] + data[14] * r.data[8]
			+ data[15] * r.data[12],
		data[12] * r.data[1] + data[13] * r.data[5] + data[14] * r.data[9]
			+ data[15] * r.data[13],
		data[12] * r.data[2] + data[13] * r.data[6] + data[14] * r.data[10]
			+ data[15] * r.data[14],
		data[12] * r.data[3] + data[13] * r.data[7] + data[14] * r.data[11]
			+ data[15] * r.data[15] };
}

template<class T>
template <uint x, uint y, uint z>
inline vec<T, 3> matrix4<T>::operator*(const base<T, x, y, z>& v) const
{
	return
	{
		*(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1] + *(T*)(&v + z) * data[2],
		*(T*)(&v + x) * data[4] + *(T*)(&v + y) * data[5] + *(T*)(&v + z) * data[6],
		*(T*)(&v + x) * data[8] + *(T*)(&v + y) * data[9] + *(T*)(&v + z) * data[10],
	};
}

template<class T>
template <uint x, uint y, uint z, uint w>
inline vec<T, 4> matrix4<T>::operator*(const base<T, x, y, z, w>& v) const
{
	return { *(T*)(&v + x) * data[0] + *(T*)(&v + y) * data[1] + *(T*)(&v + z) * data[2]
			+ *(T*)(&v + w) * data[3],
		*(T*)(&v + x) * data[4] + *(T*)(&v + y) * data[5] + *(T*)(&v + z) * data[6]
			+ *(T*)(&v + w) * data[7],
		*(T*)(&v + x) * data[8] + *(T*)(&v + y) * data[9] + *(T*)(&v + z) * data[10]
			+ *(T*)(&v + w) * data[11],
		*(T*)(&v + x) * data[12] + *(T*)(&v + y) * data[13] + *(T*)(&v + z) * data[14]
			+ *(T*)(&v + w) * data[15] };
}

template<class T>
inline T& matrix4<T>::operator()(uint r, uint c)
{
	return *(data + 4 * r + c);
}

template<class T>
inline T matrix4<T>::operator()(uint r, uint c) const
{
	return *(data + 4 * r + c);
}

template<class T>
inline matrix4<T>& matrix4<T>::operator*=(T s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	data[9] *= s;
	data[10] *= s;
	data[11] *= s;
	data[12] *= s;
	data[13] *= s;
	data[14] *= s;
	data[15] *= s;
	return *this;
}

template<class T>
inline matrix4<T>& matrix4<T>::operator/=(T s)
{
	return matrix4<T>::operator*=(1 / s);
}

template<class T>
inline matrix4<T> matrix4<T>::operator*(T s) const
{
	return matrix4<T>(*this) *= s;
}

template<class T>
inline matrix4<T> matrix4<T>::operator/(T s) const
{
	return matrix4<T>(*this) *= (1 / s);
}

template<class T>
matrix4<T>::operator matrix3<T>() const
{
	return
	{
		row[0].xyz,
		row[1].xyz,
		row[2].xyz
	};
}
template<class T>
inline matrix3<T> rotx(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		1, 0, 0,
		0, c, -s,
		0, s, c
	};
}

template<class T>
inline matrix3<T> roty(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		  c, 0, s,
		0, 1, 0,
		 -s, 0, c
	};
}

template<class T>
inline matrix3<T> rotz(T angle)
{
	T c = cosf(angle), s = sinf(angle);
	return
	{
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	};
}

template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix2<T>& m)
{
	return s << m.row[0] << m.row[1];
}
template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix3<T>& m)
{
	return s << m.row[0] << m.row[1] << m.row[2];
}
template<class T>
inline std::ostream& operator << (std::ostream& s, const matrix4<T>& m)
{
	return s << m.row[0] << m.row[1] << m.row[2] << m.row[3];
}

inline matrix4<float> perspective(float fov, float aspect, float n, float f) {
	float tan = 1 / float(tanf(fov * ct::rad * 0.5f));
	float fn = 1 / (f - n);
	return{
		tan * aspect,	0,			0,		 0,
			0,		tan,			0,		 0,
			0,		0,		-fn * (f + n),	-1,
			0,		0,	 -2 * f * n * fn,	 0
	};
}

inline matrix4<float> ortho(float l, float r, float b, float t) {
	float rl = 1 / (r - l);
	float tb = 1 / (t - b);
	return {
		2 * rl,				0,			 0,		0,
			 0,		   2 * tb,			 0,		0,
			 0,				0,			 1,		0,
		-rl * (r + l), -tb * (t + b),			0,		1
	};
}

inline matrix4<float> ortho(float l, float r, float b, float t, float n, float f) {
	float rl = 1 / (r - l);
	float tb = 1 / (t - b);
	float fn = 1 / (f - n);
	return {
		2 * rl,			 0,			 0,		0,
			 0,		2 * tb,			 0,		0,
			 0,			 0,		2 * fn,		0,
		-rl * (r + l), -tb * (t + b), -fn * (f + n),	1
	};
}

inline matrix4<float> view(const vec<float, 3>& p, const vec<float, 3>& r, const vec<float, 3>& u, const vec<float, 3>& d) {
	return{
		r.x, u.x, d.x, 0,
		r.y, u.y, d.y, 0,
		r.z, u.z, d.z, 0,
		-dot(r, p), -dot(u, p), -dot(d, p), 1
	};
}


template<class T, uint x, uint y>
inline vec<T, 2> operator *(const base<T, x, y>& v, const matrix2<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[2],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[3],
	};
}

template<class T, uint x, uint y, uint z>
inline  vec<T, 3> operator *(const base<T, x, y, z>& v, const matrix3<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[3] + *(T*)(&v + z) * m.data[6],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[4] + *(T*)(&v + z) * m.data[7],
		*(T*)(&v + x) * m.data[2] + *(T*)(&v + y) * m.data[5] + *(T*)(&v + z) * m.data[8],
	};
}


template <class T, uint x, uint y, uint z>
inline vec<T, 3> operator*(const base<T, x, y, z>& v, const matrix4<T>& m)
{
	return
	{
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[4] + *(T*)(&v + z) * m.data[8],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[5] + *(T*)(&v + z) * m.data[9],
		*(T*)(&v + x) * m.data[2] + *(T*)(&v + y) * m.data[6] + *(T*)(&v + z) * m.data[10],
	};
}

template<class T, uint x, uint y, uint z, uint w>
inline vec<T, 4> operator *(const base<T, x, y, z, w>& v, const matrix4<T>& m) {
	return {
		*(T*)(&v + x) * m.data[0] + *(T*)(&v + y) * m.data[4] + *(T*)(&v + z) * m.data[8] + *(T*)(&v + w) * m.data[12],
		*(T*)(&v + x) * m.data[1] + *(T*)(&v + y) * m.data[5] + *(T*)(&v + z) * m.data[9] + *(T*)(&v + w) * m.data[13],
		*(T*)(&v + x) * m.data[2] + *(T*)(&v + y) * m.data[6] + *(T*)(&v + z) * m.data[10] + *(T*)(&v + w) * m.data[14],
		*(T*)(&v + x) * m.data[3] + *(T*)(&v + y) * m.data[7] + *(T*)(&v + z) * m.data[11] + *(T*)(&v + w) * m.data[15]
	};
}



using mat2 = matrix2<float>;
using mat3 = matrix3<float>;
using mat4 = matrix4<float>;

inline const mat2 m2id;
inline const mat3 m3id;
inline const mat4 m4id;