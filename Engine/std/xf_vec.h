#pragma once
#include <iostream>

template<class c>
class xfvec {
	typedef unsigned uint;
	static constexpr size_t byte = sizeof(c);
	static constexpr bool destructible = !std::is_trivially_destructible<c>::value;
	size_t size_, cap_;
	c* data_;
	c* newblock(size_t n) const;
	void destruct();
	void destruct(c*, c*);
	c* copy(size_t n) const;
	void alloc();
	void alloc(size_t n);
	void range(c*& i, c*& j);
public:
	xfvec();
	xfvec(size_t n);
	xfvec(const xfvec&);
	xfvec(xfvec&&);
	xfvec(std::initializer_list<c>);
	xfvec& operator = (const xfvec&);
	xfvec& operator = (xfvec&&);
	~xfvec();
	void push(const c& item);
	void push(c&& item);
	template<class...Cs>
	void emplace(const Cs&... cs);
	template<class...Cs>
	void emplace(Cs&&... cs);
	void erase(c*, c*);
	void erase(c*);
	c* insert(c* pos, const c& item);
	c* insert(c*, c&&);
	void reverse();
	void reserve(size_t);
	void resize(size_t);
	c& operator[](size_t);
	c& operator[](size_t) const;
	void sort();
	c* find(const c&, size_t = 1) const;
	c* findif(bool (*f)(c), size_t = 1) const;
	c* findif(bool (*f)(const c&), size_t = 1) const;
	c* find(const c&, c*, c*, size_t = 1) const;
	c* findif(bool (*f)(c), c*, c*, size_t = 1) const;
	c* findif(bool (*f)(const c&), c*, c*, size_t = 1) const;
	xfvec subvec(c*, c*) const;
	xfvec map(c(*f)(c)) const;
	xfvec map(c(*f)(const c&)) const;
	template<class c2>
	xfvec<c2> map(c2(*f)(c)) const;
	template<class c2>
	xfvec<c2> map(c2(*f)(const c&)) const;
	void clear();
	bool empty() const;
	size_t size() const;
	size_t cap() const;
	c* begin() const;
	c* end() const;
	c* rbegin() const;
	c* rend() const;
	c* data() const;
	c& front() const;
	c& back() const;
	c* begin();
	c* end();
	c* rbegin();
	c* rend();
	c* data();
	c& front();
	c& back();
};


template<class c>
inline std::ostream& operator << (std::ostream& s, const xfvec<c>& v) {
	for (const c& i : v) s << i << ' ';
	return s << '\n';
}

template<class c>
inline c* xfvec<c>::newblock(size_t n) const
{
	return (c*)malloc(n * byte);
}

template<class c>
inline void xfvec<c>::destruct()
{
	if constexpr (destructible)
		for (size_t i = 0; i < size_; ++i) (data_ + i)->~c();
	free(data_);
}

template<class c>
inline void xfvec<c>::destruct(c* i, c* j)
{
	if constexpr (destructible)
		for (; i != j; ++i) i->~c();
}

template<class c>
inline c* xfvec<c>::copy(size_t n) const
{
	c* temp = newblock(n);
	for (size_t i = 0; i < size_; ++i)
		new(temp + i) c(*(data_ + i));
	return temp;
}

template<class c>
inline void xfvec<c>::alloc()
{
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, size_ * byte);
		free(data_);
		data_ = temp;
	}
}

template<class c>
inline void xfvec<c>::alloc(size_t n)
{
	if (n > cap_) {
		c* temp = newblock(cap_ = n);
		memcpy(temp, data_, size_ * byte);
		free(data_);
		data_ = temp;
	}
}

template<class c>
inline void xfvec<c>::range(c*& i, c*& j)
{
	if (i > j) {
		c* t = ++i;
		i = ++j;
		j = t;
	}
	if (!(i >= data_ && j <= data_ + size_)) throw;
}

template<class c>
inline void xfvec<c>::push(const c& item)
{
	alloc();
	new(data_ + size_++)c(item);
}

template<class c>
inline void xfvec<c>::push(c&& item)
{
	alloc();
	new(data_ + size_++)c((c&&)item);
}

template<class c>
inline void xfvec<c>::erase(c* i, c* j)
{
	range(i, j);
	destruct(i, j);
	memcpy(i, j, (data_ + size_ - j) * byte);
	size_ -= (j - i);
}

template<class c>
inline void xfvec<c>::erase(c* i)
{
	if (i < data_ || i >= data_ + size_) return;
	if constexpr (destructible) i->~c();
	memcpy(i, i + 1, (data_ + --size_ - i) * byte);

}

template<class c>
inline c* xfvec<c>::insert(c* pos, const c& item)
{
	if (pos < data_ || pos > data_ + size_) throw;
	size_t p = pos - data_;
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, p * byte);
		memcpy(temp + p + 1, data_ + p, (size_ - p) * byte);
		free(data_);
		data_ = temp;
	}
	else {
		memcpy(data_ + p + 1, data_ + p, (size_ - p) * byte);
	}
	++size_;
	return new(data_ + p) c(item);
}

template<class c>
inline c* xfvec<c>::insert(c* pos, c&& item)
{
	if (pos < data_ || pos > data_ + size_) throw;
	size_t p = pos - data_;
	if (size_ == cap_) {
		c* temp = newblock(cap_ = (cap_ + 1) * 2);
		memcpy(temp, data_, p * byte);
		memcpy(temp + p + 1, data_ + p, (size_ - p) * byte);
		free(data_);
		data_ = temp;
	}
	else {
		memcpy(data_ + p + 1, data_ + p, (size_ - p) * byte);
	}
	++size_;
	return new(data_ + p) c((c&&)item);
}

template<class c>
inline void xfvec<c>::reverse()
{
	uint size2 = size_ / 2;
	for (uint i = 0; i < size2; ++i)
	{
		c temp = data_[i];
		data_[i] = data_[size_ - i - 1];
		data_[size_ - i - 1] = temp;
	}
}

template<class c>
inline void xfvec<c>::reserve(size_t n)
{
	alloc(n);
}

template<class c>
inline void xfvec<c>::resize(size_t n)
{
	if (n > size_) {
		alloc(n);
		while (size_ != n) new(data_ + size_++)c();
	}
}

template<class c>
inline c& xfvec<c>::operator[](size_t i)
{
	if (i >= size_) throw;
	return *(data_ + i);
}

template<class c>
inline c& xfvec<c>::operator[](size_t i) const
{
	if (!(i < size_)) throw;
	return *(data_ + i);
}

template<class c>
inline void xfvec<c>::sort()
{
	static void (*swap)(c*, c*) = [](c* a, c* b) {
		c t = *a;
		*a = *b;
		*b = t;
	};
	static int (*partition)(c*, int, int) = [](c* arr, int low, int high)
	{
		c& pivot = arr[high];
		int i = (low - 1);
		for (int j = low; j <= high - 1; j++) {
			if (arr[j] <= pivot) {
				i++;
				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[i + 1], &arr[high]);
		return (i + 1);
	};
	static void (*qSort)(c*, int, int) = [](c* arr, int low, int high)
	{
		if (low < high) {
			int pi = partition(arr, low, high);
			qSort(arr, low, pi - 1);
			qSort(arr, pi + 1, high);
		}
	};
	qSort(data_, 0, size_ - 1);
}

template<class c>
inline c* xfvec<c>::find(const c& item, size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (*i == item) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(c), size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(const c&), size_t pos) const
{
	c* i = begin();
	c* j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::find(const c& item, c* i, c* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (*i == item) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(c), c* i, c* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline c* xfvec<c>::findif(bool (*f)(const c&), c* i, c* j, size_t pos) const
{
	if (!inrange(i, j)) throw;
	swapper(i, j);
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

template<class c>
inline xfvec<c> xfvec<c>::subvec(c* i, c* j) const
{
	range(i, j);
	xfvec re(j - i);
	for (; i != j; ++i) re.push(*i);
	return re;
}

template<class c>
inline xfvec<c> xfvec<c>::map(c(*f)(c)) const
{
	xfvec re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline xfvec<c> xfvec<c>::map(c(*f)(const c&)) const
{
	xfvec re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline xfvec<c>::xfvec()
	: size_(0), cap_(0), data_(nullptr)
{
}

template<class c>
inline xfvec<c>::xfvec(size_t n)
	: size_(0), cap_(n), data_(newblock(n))
{
}

template<class c>
inline xfvec<c>::xfvec(const xfvec& v)
	: size_(v.size_), cap_(v.cap_), data_(v.copy(cap_))
{
}

template<class c>
inline xfvec<c>::xfvec(xfvec&& v)
	: size_(v.size_), cap_(v.cap_), data_(v.data_)
{
	v.size_ = 0;
	v.cap_ = 0;
	v.data_ = nullptr;
}

template<class c>
inline xfvec<c>::xfvec(std::initializer_list<c> list)
	: size_(list.size()), cap_(size_), data_(newblock(cap_))
{
	for (size_t i = 0; i < size_; ++i)
		new(data_ + i) c((c&&)*(list.begin() + i));
}

template<class c>
inline xfvec<c>& xfvec<c>::operator=(const xfvec& v)
{
	destruct();
	size_ = v.size_;
	cap_ = v.cap_;
	data_ = v.copy(cap_);
	return *this;
}

template<class c>
inline xfvec<c>& xfvec<c>::operator=(xfvec&& v)
{
	destruct();
	size_ = v.size_;
	cap_ = v.cap_;
	data_ = v.data_;
	v.size_ = 0;
	v.cap_ = 0;
	v.data_ = nullptr;
	return *this;
}

template<class c>
inline xfvec<c>::~xfvec()
{
	destruct();
}

template<class c>
template<class ...Cs>
inline void xfvec<c>::emplace(const Cs& ...cs)
{
	alloc();
	new(data_ + size_++)c(cs...);
}

template<class c>
template<class ...Cs>
inline void xfvec<c>::emplace(Cs&& ...cs)
{
	alloc();
	new(data_ + size_++)c((Cs&&)cs...);
}

template<class c>
template<class c2>
inline xfvec<c2> xfvec<c>::map(c2(*f)(c)) const
{
	xfvec<c2> re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
template<class c2>
inline xfvec<c2> xfvec<c>::map(c2(*f)(const c&)) const
{
	xfvec<c2> re(size_);
	for (size_t i = 0; i < size_; ++i) re.push(f(*(data_ + i)));
	return re;
}

template<class c>
inline void xfvec<c>::clear()
{
	destruct(data_, data_ + size_);
	size_ = 0;
}

template<class c>
inline bool xfvec<c>::empty() const
{
	return size_ == 0;
}

template<class c>
inline size_t xfvec<c>::size() const
{
	return size_;
}

template<class c>
inline size_t xfvec<c>::cap() const
{
	return cap_;
}

template<class c>
inline c* xfvec<c>::begin() const
{
	return data_;
}

template<class c>
inline c* xfvec<c>::end() const
{
	return data_ + size_;
}

template<class c>
inline c* xfvec<c>::rbegin() const
{
	return data_ + size_ - 1;
}

template<class c>
inline c* xfvec<c>::rend() const
{
	return data_ - 1;
}

template<class c>
inline c* xfvec<c>::data() const
{
	return data_;
}

template<class c>
inline c& xfvec<c>::front() const
{
	return *data_;
}

template<class c>
inline c& xfvec<c>::back() const
{
	return *rbegin();
}

template<class c>
inline c* xfvec<c>::begin()
{
	return data_;
}

template<class c>
inline c* xfvec<c>::end()
{
	return data_ + size_;
}

template<class c>
inline c* xfvec<c>::rbegin()
{
	return data_ + size_ - 1;
}

template<class c>
inline c* xfvec<c>::rend()
{
	return data_ - 1;
}

template<class c>
inline c* xfvec<c>::data()
{
	return data_;
}

template<class c>
inline c& xfvec<c>::front()
{
	return *data_;
}

template<class c>
inline c& xfvec<c>::back()
{
	return *rbegin();
}
