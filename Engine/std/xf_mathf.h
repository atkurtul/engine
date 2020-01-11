#pragma once
#include "xf_constants.h"

float absl(float x);
float cpysign(float x, float y);
float ranf();
float ranpf();
bool isN(float x);
bool is0(float x);
float sign(float x);


inline float absl(float x) {
	static int abs;
	abs = *(int*)&x & 2147483647;
	return *(float*)&abs;
}

inline float cpysign(float x, float y) {
	static int sum;
	sum = *(int*)&x & 2147483648 |
		*(int*)&y & 2147483647;
	return *(float*)&sum;
}

inline float ranf() {
	return float(ct::m()) * ct::intmax2 - 1.f;
}

inline float ranpf() {
	return float(ct::m()) * ct::intmax;
}

inline bool isN(float x) {
	return *(int*)&x != -4194304 && *(int*)&x != 2139095040;
}

inline bool is0(float x) {
	return absl(x) <= FLT_EPSILON;
}

inline bool is0(double x) {
	return abs(x) <= DBL_EPSILON;
}

inline bool is0(long double x) {
	return abs(x) <= DBL_EPSILON;
}

inline float sign(float x) {
	static int sign;
	sign = (*(int*)&x & 2147483648) + 1065353216;
	return (*(float*)&sign);
}
