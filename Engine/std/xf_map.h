#pragma once
#include "xf_vec.h"
#include "xf_pair.h"
template<class key, class val>
class xfmap;
template<class key, class val>
class vref {
	friend class xfmap<key, val>;
	inline static const val val0 = val();
	inline static xfpair<key, val>* i, * j;
	key k;
	xfvec<xfpair<key, val>>& data;
	vref(const key&, xfvec<xfpair<key, val>>&);
public:
	val& operator =  (const val&);
	val& operator += (const val&);
	val& operator -= (const val&);
	val& operator *= (const val&);
	val& operator /= (const val&);
	operator const val& () const;
	const val& ref() const;
};

template<class key, class val>
class xfmap {
protected:
	xfvec<xfpair<key, val>> data;
public:
	xfmap();
	xfmap(const xfmap&);
	xfmap(xfmap&&);
	xfmap& operator = (const xfmap&);
	xfmap& operator = (xfmap&&);
	xfpair<key, val>* insert(const key&);
	xfpair<key, val>* insert(const key&, const val&);
	val* find(const key& k);
	val* find(const key& k) const;
	vref<key, val> operator[](const key&);
	const val& operator[](const key&) const;
	xfpair<key, val>* begin() const;
	xfpair<key, val>* end() const;
	xfpair<key, val>* rbegin() const;
	xfpair<key, val>* rend() const;
	bool empty() const;
	size_t size() const;
	void clear();
	xfvec<xfpair<key, val>>& container();
};


template<class key, class val>
vref<key, val>::vref(const key& k, xfvec<xfpair<key, val>>& data)
	: k(k), data(data) {}

template<class key, class val>
val& vref<key, val>::operator = (const val& n) {
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v = n;
	return data.insert(i, { k, n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator+=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v += n;
	return data.insert(i, { k, n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator-=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v -= n;
	return data.insert(i, { k, -n })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator*=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v *= n;
	return data.insert(i, { k })->v;
}

template<class key, class val>
inline val& vref<key, val>::operator/=(const val& n)
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v /= n;
	return data.insert(i, { k })->v;
}

template<class key, class val>
vref<key, val>::operator const val& () const {
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v;
	return vref<key, val>::val0;
}

template<class key, class val>
inline const val& vref<key, val>::ref() const
{
	i = data.begin(), j = data.end();
	for (; i != j && i->k <= k; ++i)
		if (i->k == k) return i->v;
	return vref<key, val>::val0;
}

template<class key, class val>
inline xfmap<key, val>::xfmap() : data()
{
}

template<class key, class val>
inline xfmap<key, val>::xfmap(const xfmap& map) : data(map.data)
{
}

template<class key, class val>
inline xfmap<key, val>::xfmap(xfmap&& map)
	: data((xfvec<xfpair<key, val>>&&)(map.data))
{
}

template<class key, class val>
inline xfmap<key, val>& xfmap<key, val>::operator=(const xfmap& map)
{
	data = map.data;
	return *this;
}

template<class key, class val>
inline xfmap<key, val>& xfmap<key, val>::operator=(xfmap&& map)
{
	data = (xfvec<xfpair<key, val>>&&)(map.data);
	return *this;
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::insert(const key& k)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin);
	return data.insert(begin, { k });
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::insert(const key& k, const val& v)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin);
	return data.insert(begin, { k, v });
}

template<class key, class val>
inline val* xfmap<key, val>::find(const key& k)
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return &begin->v;
	return 0;
}

template<class key, class val>
inline val* xfmap<key, val>::find(const key& k) const
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return &begin->v;
	return 0;
}

template<class key, class val>
inline vref<key, val> xfmap<key, val>::operator[](const key& k)
{
	return  { k, data };
}

template<class key, class val>
inline const val& xfmap<key, val>::operator[](const key& k) const
{
	xfpair<key, val>* begin = data.begin(), * end = data.end();
	for (; begin != end && begin->k <= k; ++begin)
		if (k == begin->k) return begin->v;
	return vref<key, val>::val0;
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::begin() const
{
	return data.begin();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::end() const
{
	return data.end();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::rbegin() const
{
	return data.rbegin();
}

template<class key, class val>
inline xfpair<key, val>* xfmap<key, val>::rend() const
{
	return data.rend();
}

template<class key, class val>
inline bool xfmap<key, val>::empty() const
{
	return data.empty();
}

template<class key, class val>
inline size_t xfmap<key, val>::size() const
{
	return data.size();
}

template<class key, class val>
inline void xfmap<key, val>::clear()
{
	data.clear();
}

template<class key, class val>
inline xfvec<xfpair<key, val>>& xfmap<key, val>::container()
{
	return data;
}

template<class key, class val>
inline std::ostream& operator << (std::ostream& s, const xfmap<key, val>& v) {
	for (const xfpair<key, val>& p : v) s << p;
	return s;
}