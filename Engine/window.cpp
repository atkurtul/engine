#include "clock.h"
#include "mouse.h"
#include "window.h"


void window::init(int x, int y) 
{
	glfwInit();
	_window = glfwCreateWindow(x, y, "OpenGL", 0, 0);
	_size = vec2(float(x), float(y));
	_aspect = _size.x / _size.y;
	glfwMakeContextCurrent(_window);
	gladLoadGL();
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

bool window::runs() 
{
	if (glfwWindowShouldClose(_window) || glfwGetKey(_window, GLFW_KEY_ESCAPE)) 
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
		return 0;
	}
	clock::elapse();
	mice::update();
	glfwSwapBuffers(_window);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 1;
}