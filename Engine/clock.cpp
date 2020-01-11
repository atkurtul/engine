#include "clock.h"
#include "GLFW/glfw3.h"

void clock::elapse() 
{
	static float t1 = 0.f;
	static float t2 = 0.f;
	t2 = glfwGetTime();
	_dt = t2 - t1;
	_time += _dt;
	t1 = t2;
	measureFPS();
}

void clock::measureFPS()
{
	static float cd = 0.f;
	static int counter = 0;
	static float t = 0.f;
	++counter;
	cd -= dt;
	if (cd > 0.f) return;

	_fps = counter / (_time - t);
	t = _time;
	cd = 0.5f;
	counter = 0;

}
