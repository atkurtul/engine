#pragma once
#include "xf_map.h"

template<class T>
class xfpoly {
	xfmap<int, T> c;
	T power(const T&, int);
public:
	xfpoly();
	xfpoly(const T& x);
	template<class...Ts>
	xfpoly(const Ts&...);
	xfpoly(const xfpoly&);
	xfpoly(xfpoly&&);
	vref<int, T> operator [] (size_t i);
	T  operator [] (size_t i) const;
	xfpoly& operator = (const xfpoly&);
	xfpoly& operator = (xfpoly&&);
	xfpoly& operator +=(const xfpoly&);
	xfpoly& operator -=(const xfpoly&);
	xfpoly  operator + (const xfpoly&);
	xfpoly  operator - (const xfpoly&);
	xfpoly  operator * (const xfpoly&);
	xfpoly& operator *=(const xfpoly&);
	xfpoly divide(const T&);
	void resize(size_t);
	int degree() const;
	xfpoly derivative() const;
	T discriminant() const;
	T operator()(const T&);
	xfvec<T> roots();
	T root1();
	const xfmap<int, T>& coeffs() const;
};



template<class T>
std::ostream& operator << (std::ostream& s, const xfpoly<T>& p) {
	return s << p.coeffs();
}

template<class T>
inline T xfpoly<T>::power(const T& n, int p)
{
	if (p == 0) return 1;
	T re = n;
	while (--p, p > 0)re *= n;
	return re;
}

template<class T>
inline xfpoly<T>::xfpoly()
{
}

template<class T>
inline xfpoly<T>::xfpoly(const T& x)
{
	c[0] = x;
}

template<class T>
template<class ...Ts>
inline xfpoly<T>::xfpoly(const Ts& ... t)
{
	static int i = 0;
	i = -1;
	((c[++i] = t), ...);
}

template<class T>
inline xfpoly<T>::xfpoly(const xfpoly& p) : c(p.c)
{
}

template<class T>
inline xfpoly<T>::xfpoly(xfpoly&& p) : c((xfmap<int, T>&&)(p.c))
{
}

template<class T>
inline vref<int, T> xfpoly<T>::operator[](size_t i)
{
	return c[i];
}

template<class T>
inline T xfpoly<T>::operator[](size_t i) const
{
	return c[i];
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator=(const xfpoly& p)
{
	c = p.c;
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator=(xfpoly&& p)
{
	c = (xfmap<int, T>&&)(p.c);
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator+=(const xfpoly& p)
{
	for (int i = p.degree(); i >= 0; ++i) c[i] += p[i];
	return *this;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator-=(const xfpoly& p)
{
	for (int i = p.degree(); i >= 0; ++i) c[i] -= p[i];
	return *this;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator+(const xfpoly& p)
{
	return xfpoly(*this) += p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator-(const xfpoly& p)
{
	return xfpoly(*this) -= p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::operator * (const xfpoly& p)
{
	int d1 = degree(), d2 = p.degree();
	xfpoly re;
	for (int i = 0; i <= d1; ++i)
		for (int j = 0; j <= d2; ++j)
			re[i + j] += c[i] * p[j];
	return re;
}

template<class T>
inline xfpoly<T>& xfpoly<T>::operator*=(const xfpoly& p)
{
	return *this = *this * p;
}

template<class T>
inline xfpoly<T> xfpoly<T>::divide(const T& root)
{
	int d = degree();
	xfpoly div;
	for (int i = 0; i < d; i++)
		for (int j = i; j < d; j++)
			div.c[i] += c[j + 1] * power(root, j - i);
	return div;
}

template<class T>
inline void xfpoly<T>::resize(size_t n)
{
	c.resize(n);
}

template<class T>
inline int xfpoly<T>::degree() const
{
	if (!c.empty())
		return c.rbegin()->k;
	return 0;
}

template<class T>
inline xfpoly<T> xfpoly<T>::derivative() const
{
	xfpoly re;
	for (const xfpair<int, T>& n : c) {
		T x = n.k * c[n.k];
		if (x != 0)
			re[n.k - 1] = x;
	}
	return re;
}

template<class T>
inline T xfpoly<T>::discriminant() const
{
	return T();
}

template<class T>
inline T xfpoly<T>::operator()(const T& in)
{
	T re = 0;
	for (const xfpair<int, T>& n : c)
		re += n.v * power(in, n.k);
	return re;
}

template<class T>
inline xfvec<T> xfpoly<T>::roots()
{
	xfvec<T> re;
	T r = root1();
	xfpoly p = *this;
	while (p.degree() != 0) {
		re.push(r);
		p = p.divide(r);
		r = p.root1();
	}
	return re;
}

template<class T>
T  xfpoly<T>::root1() {
	xfpoly der = derivative();
	T p = der(0);
	T y = operator()(0);
	T x = -y / p;
	int it = 0;
	while (!is0(y)) {
		it++;
		if (is0(p)) {
			//std::cout << y << "derivative is 0\n";
			T r = T(rand() % 100) - 200.;
			x = operator()(r) / der(r);
			y = operator()(x);
			p = der(x);
		}
		else {
			x = x - y / p;
			y = operator()(x);
			p = der(x);
			//cout << x << "\n";
		}
		if (it > 200) return x;
	}
	return x;
}

template<class T>
inline const xfmap<int, T>& xfpoly<T>::coeffs() const
{
	return c;
}
