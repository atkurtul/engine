#pragma once
#include "std/xf_vmath_vec.h"
class window;
class mice 
{
	friend class window;
	inline static double _x = 0, _y = 0;
	inline static bool _status = 1;
	inline static vec2 _pos = 0;
	inline static vec2 _delta = 0;
	static void update();
public:
	static void reset();
	static void hide();
	static void show();
	static void toggle();
	static vec4 normalized();

	inline static const float& x = _pos.x;
	inline static const float& y = _pos.x;
	inline static const float& dx = _delta.x;
	inline static const float& dy = _delta.y;
	inline static const vec2& pos = _pos;
	inline static const vec2& delta = _delta;
	inline static const bool& status = _status;
};
