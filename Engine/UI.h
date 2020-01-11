#pragma once
#include "font.h"
#include "shader.h"

struct text
{
	xfstr str;
	vec2 pos;
	float scale;
};

class UI
{
	font _font;
	xfvec<text> _texts;
	shader _sh;
public:
	UI(const char* font);
	void render();
	void renderText(const xfstr& text, float x, float y, float scale = 1.f);
};