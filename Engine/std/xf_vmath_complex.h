#pragma once
#include <iostream>

template<class T>
struct complex {
	union {
		struct { T x, y; };
		T data[2];
	};
	complex() {}
	complex(T x, T y) : data{ x, y } {}
	complex(T x) : data{ x, 0 } {}
	T phase() const;
	T len2() const;
	T len() const;
	complex operator -() const;
	complex operator ~() const;
	complex& operator +=(const complex&);
	complex& operator -=(const complex&);
	complex  operator + (const complex&) const;
	complex  operator - (const complex&) const;
	complex& operator +=(T);
	complex& operator -=(T);
	complex& operator *=(T);
	complex& operator /=(T);
	complex  operator + (T) const;
	complex  operator - (T) const;
	complex  operator * (T) const;
	complex  operator / (T) const;
	complex  operator * (const complex&) const;
	complex  operator / (const complex&) const;
	complex& operator *=(const complex&);
	complex& operator /=(const complex&);
};


template<class T>
inline std::ostream& operator << (std::ostream& s, const complex<T>& c) {
	return s << c.x << ' ' << c.y << '\n';
}

template<class T>
inline T complex<T>::phase() const
{
	return atan2(y, x);
}

template<class T>
inline T complex<T>::len2() const
{
	return x * x + y * y;
}

template<class T>
inline T complex<T>::len() const
{
	return sqrtf(len2());
}

template<class T>
inline complex<T> operator * (T n, const complex<T>& c)
{
	return { n * c.x, n * c.y };
}

template<class T>
inline complex<T> operator / (T n, const complex<T>& c)
{
	n /= c.len2();
	return { n * c.x, -n * c.y };
}

template<class T>
inline complex<T> complex<T>::operator-() const
{
	return { -x, -y };
}

template<class T>
inline complex<T> complex<T>::operator~() const
{
	return { x, -y };
}

template<class T>
inline complex<T>& complex<T>::operator+=(const complex& c)
{
	x += c.x; y += c.y;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator-=(const complex& c)
{
	x -= c.x; y -= c.y;
	return *this;
}

template<class T>
inline complex<T> complex<T>::operator+(const complex& c) const
{
	return { x + c.x, y + c.y };
}

template<class T>
inline complex<T> complex<T>::operator-(const complex& c) const
{
	return { x - c.x, y - c.y };
}

template<class T>
inline complex<T>& complex<T>::operator+=(T n)
{
	x += n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator-=(T n)
{
	x -= n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator*=(T n)
{
	x *= n; y *= n;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator/=(T n)
{
	n = static_cast<T>(1) / n;
	x *= n; y *= n;
	return *this;
}

template<class T>
inline complex<T> complex<T>::operator+(T n) const
{
	return { x + n, y };
}

template<class T>
inline complex<T> complex<T>::operator-(T n) const
{
	return { x - n, y };
}

template<class T>
inline complex<T> complex<T>::operator*(T n) const
{
	return { x * n, y * n };
}

template<class T>
inline complex<T> complex<T>::operator/(T n) const
{
	n = static_cast<T>(1) / n;
	return { x * n, y * n };
}

template<class T>
inline complex<T> complex<T>::operator*(const complex& c) const
{
	return { x * c.x - y * c.y, x * c.y + y * c.x };
}

template<class T>
inline complex<T> complex<T>::operator/(const complex& c) const
{
	T l = static_cast<T>(1) / c.len2();
	return { l * (x * c.x + y * c.y), l * (y * c.x - x * c.y) };
}

template<class T>
inline complex<T>& complex<T>::operator*=(const complex& c)
{
	T t = x;
	x = x * c.x - y * c.y;
	y = t * c.y + y * c.x;
	return *this;
}

template<class T>
inline complex<T>& complex<T>::operator/=(const complex& c)
{
	T t = x; T l = static_cast<T>(1) / c.len2();
	x = (x * c.x + y * c.y) * l;
	y = (y * c.x - t * c.y) * l;
	return *this;
}
