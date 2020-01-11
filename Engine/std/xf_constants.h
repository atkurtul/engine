#pragma once
#include <random>
#include <time.h>
typedef unsigned int uint;
struct ct {
	static constexpr float intmax2 = 2.f / INT_MAX;
	static constexpr float intmax = 1.f / INT_MAX;
	inline static std::mt19937 m = std::mt19937((uint)time(0));
	static constexpr float eps = FLT_EPSILON;
	static constexpr float e = 2.7182818284590452353f;
	static constexpr float tau = 6.2831853071795864769f;
	static constexpr float pi = 3.1415926535897932384f;
	static constexpr float pi_2 = 1.5707963267948966192f;
	static constexpr float pi_3 = 1.0471975511965977461f;
	static constexpr float pi_4 = 0.7853981633974483096f;
	static constexpr float pi_5 = 0.6283185307179586476f;
	static constexpr float pi_6 = 0.5235987755982988730f;
	static constexpr float pi_9 = 0.3490658503988659153f;
	static constexpr float pi_10 = 0.3141592653589793238f;
	static constexpr float pi_12 = 0.2617993877991494365f;
	static constexpr float pi_15 = 0.2094395102393195492f;
	static constexpr float pi_18 = 0.1745329251994329576f;
	static constexpr float pi_20 = 0.1570796326794896619f;
	static constexpr float pi_30 = 0.1047197551196597746f;
	static constexpr float pi_36 = 0.0872664625997164788f;
	static constexpr float pi_45 = 0.0698131700797731830f;
	static constexpr float pi_60 = 0.0523598775598298873f;
	static constexpr float pi_90 = 0.0349065850398865915f;
	static constexpr float rad = 0.0174532925199432957f;
	static constexpr float deg = 57.295779513082320876f;
	static constexpr float sqrt2 = 1.4142135623730950488f;
	static constexpr float sqrt3 = 1.7320508075688772935f;
	static constexpr float sqrt5 = 2.2360679774997896964f;
	static constexpr float sqrt10 = 3.1622776601683793319f;
	static constexpr float half = 0.5f;
	static constexpr float _3half = 1.5f;
};
