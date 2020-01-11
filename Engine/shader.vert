#version 460
layout (location = 0) in vec4 v;
layout (location = 1) in vec3 n;
layout (location = 2) in vec2 t;
layout (location = 3) in vec4 c;
out vec2 tex;
out vec4 col;
out vec3 fpos;
out vec3 normal;

uniform mat4 prj;
uniform mat4 view;
uniform mat4 xform[200];

void main() 
{
	normal = mat3(xform[gl_InstanceID]) * n;
	fpos = (xform[gl_InstanceID] * v).xyz;
	gl_Position = prj * view * vec4(fpos, 1);
	col = c;
	tex = t;
}