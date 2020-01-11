#pragma once
#include "window.h"

struct key
{
	enum
	{
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Right = GLFW_MOUSE_BUTTON_RIGHT,
		Mid = GLFW_MOUSE_BUTTON_MIDDLE,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		SPACE = GLFW_KEY_SPACE,
		ESCAPE = GLFW_KEY_ESCAPE,
		ENTER = GLFW_KEY_ENTER,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		INSERT = GLFW_KEY_INSERT,
		DEL = GLFW_KEY_DELETE,
		RightArrow = GLFW_KEY_RIGHT,
		LeftArrow = GLFW_KEY_LEFT,
		DownArrow = GLFW_KEY_DOWN,
		UpArrow = GLFW_KEY_UP,
		PAGE_UP = GLFW_KEY_PAGE_UP,
		PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		HOME = GLFW_KEY_HOME,
		END = GLFW_KEY_END,
		CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
		NUM_LOCK = GLFW_KEY_NUM_LOCK,
		PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
		PAUSE = GLFW_KEY_PAUSE,
		SHIFT = GLFW_KEY_LEFT_SHIFT,
		CONTROL = GLFW_KEY_LEFT_CONTROL,
		ALT = GLFW_KEY_LEFT_ALT,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12
	};
};

struct input
{
	int key;
	input(int key);
	operator bool();
};

inline input::input(int key) 
	: key(key) 
{
}

inline input::operator bool()
{
	return key < 3 ? glfwGetMouseButton(window::win, key) : glfwGetKey(window::win, key);
}