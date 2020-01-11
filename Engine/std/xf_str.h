#pragma once
#include "xf_constants.h"
#include <iostream>
#include <fstream>

class xfstr {
	size_t size_, cap_;
	char* data_;
	char* newblock(size_t n) const;
	char* copy(size_t n) const;
	void alloc();
	void alloc(size_t n);
	void range(char*& i, char*& j) const;
	static bool NaN(char);
	static bool N(char);
	static bool WS(char);
	static bool NWS(char);
	static bool dot(char);

public:
	xfstr();
	xfstr(size_t n);
	xfstr(const char*);
	xfstr(const xfstr&);
	xfstr(xfstr&&) noexcept;
	xfstr& operator = (const xfstr&);
	xfstr& operator = (xfstr&&) noexcept;
	~xfstr();
	xfstr& operator +=(char);
	xfstr& operator +=(const char*);
	xfstr& operator +=(const xfstr&);
	xfstr  operator +(char) const;
	xfstr  operator +(const char*) const;
	xfstr  operator +(const xfstr&) const;
	bool operator == (const char*) const;
	bool operator != (const char*) const;
	bool operator == (const xfstr&) const;
	bool operator != (const xfstr&) const;
	bool operator <  (const xfstr&) const;
	bool operator <= (const xfstr&) const;
	bool operator >  (const xfstr&) const;
	bool operator >= (const xfstr&) const;

	xfstr& operator << (int n);
	xfstr& operator << (uint n);
	xfstr& operator << (long);
	xfstr& operator << (unsigned long);
	xfstr& operator << (float);
	xfstr& operator << (double);
	xfstr& operator >> (long& n);
	xfstr& operator >> (unsigned long&);
	xfstr& operator >> (int& n);
	xfstr& operator >> (uint& n);
	xfstr& operator >> (float&);
	xfstr& operator >> (double&);
	xfstr& read(const char*);
	std::istream& getline(std::istream&, char = '\n');
	void erase(char*, char*);
	void erase(char* i);
	const char* c_str() const;
	char** ptr();
	operator const char* () const;
	uint count(const char*) const;
	char* find(const char*, uint = 1) const;
	char* find(const char*, char*, uint = 1) const;
	char* find(char, size_t = 1) const;
	char* findif(bool (*f)(char), size_t = 1) const;
	char* find(char, char*, char*, size_t = 1) const;
	char* findif(bool (*f)(char), char*, char*, size_t = 1) const;
	xfstr substr(const char*, const char*, uint = 1);
	xfstr inbtwn(char a, char b) const;
	xfstr exbtwn(char a, char b) const;
	xfstr substr(size_t, size_t) const;
	xfstr substr(size_t) const;
	xfstr map(char(*f)(char)) const;
	xfstr& cls();
	void clear();
	bool empty() const;
	size_t size() const;
	size_t cap() const;
	char* begin() const;
	char* end() const;
	char* rbegin() const;
	char* rend() const;
	char* data() const;
	char* begin();
	char* end();
	char* rbegin();
	char* rend();
	char* data();
};

std::ostream& operator << (std::ostream& s, const xfstr& str);
std::istream& operator >> (std::istream& s, xfstr& str);
xfstr operator + (const char* c, const xfstr& s);
xfstr tostr(float x);
xfstr tostr(double x);
xfstr tostr(long x);
xfstr tostr(unsigned long x);
xfstr tostr(int x);
inline xfstr tostr(uint x);


inline char* xfstr::newblock(size_t n) const
{
	return (char*)malloc(n);
}

inline char* xfstr::copy(size_t n) const
{
	char* temp = newblock(n);
	memcpy(temp, data_, size_ + 1);
	return temp;
}

inline void xfstr::alloc()
{
	if (size_ + 1 == cap_) {
		char* temp = copy(cap_ = (cap_ + 1) * 2);
		free(data_);
		data_ = temp;
	}
}

inline void xfstr::alloc(size_t n)
{
	if (n > cap_) {
		char* temp = copy(cap_ = n);
		free(data_);
		data_ = temp;
	}
}

inline void xfstr::range(char*& i, char*& j) const
{
	if (i > j) {
		char* t = ++i;
		i = ++j;
		j = t;
	}
	if (!(i >= data_ && j <= data_ + size_)) throw;
}


inline bool xfstr::NaN(char c)
{
	return c < 48 || c > 57;
}

inline bool xfstr::N(char c)
{
	return c > 47 && c < 58;
}

inline bool xfstr::WS(char c)
{
	return c == 32;
}

inline bool xfstr::NWS(char c)
{
	return c != 32;
}

inline bool xfstr::dot(char c)
{
	return c == 46;
}

inline xfstr::xfstr()
	: size_(0), cap_(1), data_(new char(0))
{
}

inline xfstr::xfstr(size_t n)
	: size_(n), cap_(n + 1), data_(newblock(cap_))
{
	new(data_ + size_)char(0);
}

inline xfstr::xfstr(const char* c)
	: size_(strlen(c)), cap_(size_ + 1), data_(newblock(cap_))
{
	memcpy(data_, c, cap_);
}

inline xfstr::xfstr(const xfstr& s)
	: size_(s.size_), cap_(s.cap_), data_(s.copy(cap_))
{
}

inline xfstr::xfstr(xfstr&& s) noexcept
	: size_(s.size_), cap_(s.cap_), data_(s.data_)
{
	s.data_ = nullptr;
}

inline xfstr& xfstr::operator=(const xfstr& s)
{
	free(data_);
	size_ = s.size_;
	cap_ = s.cap_;
	data_ = s.copy(cap_);
	return *this;
}

inline xfstr& xfstr::operator=(xfstr&& s) noexcept
{
	free(data_);
	size_ = s.size_;
	cap_ = s.cap_;
	data_ = s.data_;
	s.data_ = nullptr;
	return *this;
}

inline xfstr::~xfstr()
{
	free(data_);
}

inline xfstr& xfstr::operator+=(char c)
{
	alloc();
	new(data_ + size_++)char(c);
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr& xfstr::operator+=(const char* c)
{
	size_t len = strlen(c);
	alloc(size_ + len + 1);
	memcpy(data_ + size_, c, len);
	size_ += len;
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr& xfstr::operator+=(const xfstr& s)
{
	alloc(size_ + s.size_ + 1);
	memcpy(data_ + size_, s.data_, s.size_);
	size_ += s.size_;
	new(data_ + size_)char(0);
	return *this;
}

inline xfstr xfstr::operator +(char c) const
{
	xfstr re(size_ + 1);
	memcpy(re.data_, data_, size_);
	new(re.data_ + size_)char(c);
	return re;
}

inline xfstr xfstr::operator +(const char* c) const
{
	size_t len = strlen(c);
	xfstr re(size_ + len);
	memcpy(re.data_, data_, size_);
	memcpy(re.data_ + size_, c, len);
	return re;
}

inline xfstr xfstr::operator +(const xfstr& s) const
{
	xfstr re(size_ + s.size_);
	memcpy(re.data_, data_, size_);
	memcpy(re.data_ + size_, s.data_, s.size_);
	return re;
}

inline bool xfstr::operator==(const char* c) const
{
	return strcmp(data_, c) == 0;
}

inline bool xfstr::operator!=(const char* c) const
{
	return strcmp(data_, c) != 0;
}

inline bool xfstr::operator==(const xfstr& s) const
{
	return strcmp(data_, s.data_) == 0;
}

inline bool xfstr::operator!=(const xfstr& s) const
{
	return strcmp(data_, s.data_) != 0;
}

inline bool xfstr::operator<(const xfstr& s) const
{
	return strcmp(data_, s.data_) < 0;;
}

inline bool xfstr::operator<=(const xfstr& s) const
{
	return strcmp(data_, s.data_) <= 0;;
}

inline bool xfstr::operator>(const xfstr& s) const
{
	return strcmp(data_, s.data_) > 0;;
}

inline bool xfstr::operator>=(const xfstr& s) const
{
	return strcmp(data_, s.data_) >= 0;;
}

inline xfstr& xfstr::operator<<(int n)
{
	const uint len = static_cast<uint>(_scprintf("%d", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%d", n);
	return *this;
}

inline xfstr& xfstr::operator<<(uint n)
{
	const uint len = static_cast<uint>(_scprintf("%u", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%u", n);
	return *this;
}

inline xfstr& xfstr::operator<<(long n)
{
	const uint len = static_cast<uint>(_scprintf("%d", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%d", n);
	return *this;
}

inline xfstr& xfstr::operator<<(unsigned long n)
{
	const uint len = static_cast<uint>(_scprintf("%ul", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%ul", n);
	return *this;
}

inline xfstr& xfstr::operator<<(float n)
{
	const uint len = static_cast<uint>(_scprintf("%f", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%f", n);
	return *this;
}

inline xfstr& xfstr::operator<<(double n)
{
	const uint len = static_cast<uint>(_scprintf("%f", n));
	free(data_);
	data_ = newblock(len + 1);
	sprintf_s(data_, len + 1, "%f", n);
	return *this;
}

inline xfstr& xfstr::operator>>(long& n)
{
	static char* end;
	n = strtol(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(unsigned long& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(int& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(uint& n)
{
	static char* end;
	n = strtoul(data_, &end, 10);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(float& n)
{
	static char* end;
	n = strtof(data_, &end);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::operator>>(double& n)
{
	static char* end;
	n = strtod(data_, &end);
	erase(data_, end);
	return *this;
}

inline xfstr& xfstr::read(const char* file)
{
	static char c;
	std::ifstream s(file);
	if (!s)
	{
		std::cout << "Cannot find file " << file << '\n';
		return *this;
	}
	size_ = 0;
	while (s.get(c)) *this += c;
	s.close();
	return *this;
}

inline std::istream& xfstr::getline(std::istream& s, char delim)
{
	clear();
	static char c;
	while (s.get(c) && c != delim) operator+=(c);
	return s;
}

inline void xfstr::erase(char* i, char* j)
{
	range(i, j);
	memcpy(i, j, data_ + size_ - j);
	size_ -= (j - i);
	new(data_ + size_)char(0);

}

inline void xfstr::erase(char* i)
{
	if (i < data_ || i >= data_ + size_) return;
	memcpy(i, i + 1, data_ + size_ - i - 1);
	new(data_ + --size_)char(0);
}

inline const char* xfstr::c_str() const
{
	return data_;
}

inline char** xfstr::ptr()
{
	return &data_;
}

inline xfstr::operator const char* () const
{
	return data_;
}

inline char* xfstr::data() const
{
	return data_;
}

inline char* xfstr::begin()
{
	return data_;
}

inline char* xfstr::end()
{
	return data_ + size_;
}

inline char* xfstr::rbegin()
{
	return data_ + size_ - 1;
}

inline char* xfstr::rend()
{
	return data_ - 1;
}

inline char* xfstr::data()
{
	return data_;
}

inline uint xfstr::count(const char* str) const
{
	static uint len, lim, c;
	len = strlen(str);
	if (size_ < len) return 0;
	lim = size_ - len + 1;
	c = 0;
	bool state = 1;
	for (uint i = 0; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					state = 0;
					break;
				}
			}
			if (state) ++c;
			state = 1;
		}
	}
	return c;
}

inline char* xfstr::find(const char* str, uint pos) const
{
	static uint len, lim;
	len = strlen(str);
	if (size_ < len) return 0;
	lim = size_ - len + 1;
	char* c = 0;
	for (uint i = 0; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			c = data_ + i;
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					c = 0;
					break;
				}
			}
			if (c)
			{
				--pos;
				if (pos == 0) return c;
			}
		}
	}
	return c;
}

inline char* xfstr::find(const char* str, char* begin_, uint pos) const
{
	static uint len, lim, begin;
	len = strlen(str);
	begin = begin_ - data_;
	if (size_ - begin < len) return 0;
	lim = size_ - len + 1;
	char* c = 0;
	for (uint i = begin; i < lim; ++i)
	{
		if (data_[i] == str[0])
		{
			c = data_ + i;
			for (uint j = 1; j < len; ++j)
			{
				if (data_[i + j] != str[j])
				{
					c = 0;
					break;
				}
			}
			if (c)
			{
				--pos;
				if (pos == 0) return c;
			}
		}
	}
	return c;
}

inline char* xfstr::find(char c, size_t pos) const
{
	static char* i, * j;
	i = begin();
	j = end();
	for (; i != j; ++i) {
		if (*i == c) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::findif(bool (*f)(char), size_t pos) const
{
	static char* i, * j;
	i = begin();
	j = end();
	for (; i != j; ++i) {
		if (f(*i)) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::find(char c, char* i, char* j, size_t pos) const
{
	range(i, j);
	for (; i != j; ++i) {
		if (*i == c) {
			--pos;
			if (!pos) return i;
		}
	}
	return 0;
}

inline char* xfstr::findif(bool (*f)(char), char* i, char* j, size_t pos) const
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

inline xfstr xfstr::substr(const char* a, const char* b, uint pos)
{
	static char* i, * j;
	i = find(a, pos);
	j = find(b, pos) + strlen(b);
	return substr(i - data_, j - i);
}

inline xfstr xfstr::exbtwn(char a, char b) const
{
	static char* i, * j;
	i = find(a);
	j = find(b, ++i, end());
	return substr(i - data_, j - i);
}
inline xfstr xfstr::inbtwn(char a, char b) const
{
	static char* i, * j;
	i = find(a);
	j = find(b, i + 1, end());
	return substr(i - data_, ++j - i);
}
inline xfstr xfstr::substr(size_t pos, size_t len) const
{
	if (pos >= size_) return xfstr();
	xfstr re(len);
	memcpy(re.data_, data_ + pos, len);
	new(re.data_ + re.size_)char(0);
	return re;
}

inline xfstr xfstr::substr(size_t pos) const
{
	if (pos >= size_) return xfstr();
	xfstr re(size_ - pos);
	memcpy(re.data_, data_ + pos, re.size_);
	new(re.data_ + re.size_)char(0);
	return re;
}

inline xfstr xfstr::map(char(*f)(char)) const
{
	char* re = new char[size_ + 1];
	for (size_t i = 0; i < size_; ++i) re[i] = f(*(data_ + i));
	re[size_] = 0;
	return re;
}

inline xfstr& xfstr::cls()
{
	if (empty()) return *this;
	while (*data_ == ' ' || *data_ == 9 || *data_ == '\n')
	{
		erase(data_);
		if (empty()) return *this;
	}
	while (*(data_ + size_ - 1) == ' ' || *(data_ + size_ - 1) == 9 || *(data_ + size_ - 1) == '\n')
	{
		erase(data_ + size_ - 1);
		if (empty()) return *this;
	}
	return *this;
}

inline void xfstr::clear()
{
	size_ = 0;
}

inline bool xfstr::empty() const
{
	return size_ == 0;
}

inline size_t xfstr::size() const
{
	return size_;
}

inline size_t xfstr::cap() const
{
	return cap_;
}

inline char* xfstr::begin() const
{
	return data_;
}

inline char* xfstr::end() const
{
	return data_ + size_;
}

inline char* xfstr::rbegin() const
{
	return data_ + size_ - 1;
}

inline char* xfstr::rend() const
{
	return data_ - 1;
}

inline std::ostream& operator << (std::ostream& s, const xfstr& str) {
	return s << str.data();
}

inline std::istream& operator>>(std::istream& s, xfstr& str)
{
	static char c;
	str.clear();
	while (s.get(c)) str += c;
	return s;
}

inline xfstr operator + (const char* c, const xfstr& s) {
	static uint len;
	len = strlen(c);
	xfstr re(len + s.size());
	memcpy(re.data(), c, len);
	memcpy(re.data() + len, s.data(), s.size());
	return re;
}

inline xfstr tostr(float x) {
	const uint len = static_cast<uint>(_scprintf("%f", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%f", x);
	return re;
}

inline xfstr tostr(double x) {
	const uint len = static_cast<uint>(_scprintf("%f", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%f", x);
	return re;
}

inline xfstr tostr(long x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}

inline xfstr tostr(unsigned long x) {
	const uint len = static_cast<uint>(_scprintf("%ul", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%ul", x);
	return re;
}

inline xfstr tostr(int x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}

inline xfstr tostr(uint x) {
	const uint len = static_cast<uint>(_scprintf("%d", x));
	xfstr re(len);
	sprintf_s(re.data(), len + 1, "%d", x);
	return re;
}