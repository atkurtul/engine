#include "cam.h"
#include "clock.h"
#include "mouse.h"
#include "input.h"

void cam::look()
{
	mat3 x = roty(-mice::delta.x * clock::dt);
	_right = _right * x;
	quat xy = x * axang(right, mice::delta.y * clock::dt);
	_dir = _dir * xy;
	_up = _up * xy;
}

void cam::move()
{
	float s = speed * clock::dt;
	if (input(key::D)) _pos += _right * s;
	if (input(key::A)) _pos -= _right * s;
	if (input(key::W)) _pos += _dir * s;
	if (input(key::S)) _pos -= _dir * s;
}

void cam::update()
{
	look();
	move();
	_view.row[3].xyz = -_pos * view;
}
