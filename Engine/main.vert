#version 460
layout (location = 0) in vec4 v;
void main()
{
	gl_Position = v;
}