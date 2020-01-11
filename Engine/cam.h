#pragma once
#include "std/xf_vmath.h"

class cam
{
	mat4 _prj;
	mat4 _view;
	dvec3& _right = _view.col[0].xyz;
	dvec3& _up	= _view.col[1].xyz;
	dvec3& _dir = _view.col[2].xyz;
	vec3 _pos;

public:
	float speed = 10.f;
	const mat4& prj = _prj;
	const mat4& view = _view;
	const dvec3& right = _right;
	const dvec3& up = _up;
	const dvec3& dir = _dir;
	const vec3& pos = _pos;

	void look();
	void move();
	void update();
};