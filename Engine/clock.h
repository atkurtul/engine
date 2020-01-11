#pragma once
class window;
class clock 
{
	inline static float _dt = 0.f;
	inline static float _time = 0.f;
	inline static float _fps = 0.f;
	static void elapse();
	static void measureFPS();
	friend class window;
public:
	inline static const float& dt = _dt;
	inline static const float& time = _time;
	inline static const float& fps = _fps;
};