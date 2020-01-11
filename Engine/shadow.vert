#version 460 core
layout (location = 0) in vec4 v;

uniform mat4 prj;
uniform mat4 view;
uniform mat4 xform[200];

void main() {
  	gl_Position = prj * view * xform[gl_InstanceID] * v;
}  