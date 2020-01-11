#pragma once
#include <iostream>

template<class key, class val>
struct xfpair {
	key k;
	val v;
	xfpair();
	xfpair(const key& k);
	xfpair(const key& k, const val& v);
	xfpair(const xfpair& p);
	xfpair& operator = (const xfpair& p);
	xfpair(xfpair&& p);
	xfpair& operator = (xfpair&& p);
	bool operator > (const xfpair& p) const;
	bool operator < (const xfpair& p) const;
	bool operator ==(const xfpair& p) const;
	bool operator <=(const xfpair& p) const;
	bool operator >=(const xfpair& p) const;
	bool operator !=(const xfpair& p) const;
};


template<class key, class val>
inline std::ostream& operator << (std::ostream& s, const xfpair<key, val>& p) {
	return s << '<' << p.k << ',' << p.v << '>';
}

template<class key, class val>
inline xfpair<key, val>::xfpair() : k(), v()
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const key& k) : k(k), v()
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const key& k, const val& v) : k(k), v(v)
{
}

template<class key, class val>
inline xfpair<key, val>::xfpair(const xfpair& p) : k(p.k), v(p.v)
{
}

template<class key, class val>
inline xfpair<key, val>& xfpair<key, val>::operator=(const xfpair& p)
{
	k = p.k; v = p.v;
	return *this;
}

template<class key, class val>
inline xfpair<key, val>::xfpair(xfpair&& p)
	: k((key&&)p.k), v((val&&)p.v)
{
}

template<class key, class val>
inline xfpair<key, val>& xfpair<key, val>::operator=(xfpair&& p)
{
	k = (key&&)p.k;
	v = (val&&)p.v;
	return *this;
}

template<class key, class val>
inline bool xfpair<key, val>::operator<(const xfpair& p) const
{
	return k < p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator>(const xfpair& p) const
{
	return k > p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator==(const xfpair& p) const
{
	return k == p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator<=(const xfpair& p) const
{
	return k <= p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator>=(const xfpair& p) const
{
	return k >= p.k;
}

template<class key, class val>
inline bool xfpair<key, val>::operator!=(const xfpair& p) const
{
	return k != p.k;
}