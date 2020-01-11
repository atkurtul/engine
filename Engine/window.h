#pragma once
#include "std/xf_vmath_vec.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class window 
{
	inline static GLFWwindow* _window = nullptr;
	inline static vec2 _size;
	inline static float _aspect;
public:
	static void init(int x, int y);
	static bool runs();

	inline static GLFWwindow*& win = _window;
	inline static const vec2& size = _size;
	inline static const float& aspect = _aspect;
};

