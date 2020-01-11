#include "mouse.h"
#include "window.h"

void mice::reset() 
{
	glfwSetCursorPos(window::win, window::size.x * 0.5, window::size.y * 0.5);
}

void mice::hide() 
{
	if (_status) 
	{
		reset();
		_status = 0;
	}
	glfwSetInputMode(window::win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void mice::show() 
{
	_status = 1;
	glfwSetInputMode(window::win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void mice::toggle() 
{
	_status = !_status;
	_status ? show() : hide();
}

void mice::update() 
{
	glfwGetCursorPos(window::win, &_x, &_y);
	_pos.x = float(_x);
	_pos.y = window::size.y - float(_y);
	if (_status) 
	{
		vec2 prev = _pos;
		_delta = _pos - prev;
		prev = _pos;
	}
	else 
	{
		_delta = _pos - window::size * 0.5f;
		glfwSetCursorPos(window::win, window::size.x * 0.5, window::size.y * 0.5);
	}
}

vec4 mice::normalized()
{
	vec2 re = 2.f * (mice::pos / window::size);
	re.y = 2.f - re.y;
	return vec4(re - 1.f, 0.f, 1.f);
}
