#include "UI.h"
#include "window.h"


UI::UI(const char* font)
	: _font(font, 0.3f)
{
	const char* defaultvshader =
		"#version 460												\n"
		"layout (location = 0) in vec2 v;							\n"
		"layout (location = 1) in vec2 t;							\n"
		"out vec2 tex;												\n"
		"uniform vec3 xform;										\n"
		"uniform mat4 prj;											\n"
		"void main()												\n"
		"{															\n"
		"	tex = t;												\n"
		"	gl_Position = prj * vec4(xform.z * v + xform.xy, 0, 1);	\n"
		"}															\n";
	const char* defaultfshader =
		"#version 460											 \n"
		"out vec4 col;											 \n"
		"in vec2 tex;											 \n"
		"uniform sampler2D glyph;								 \n"
		"void main()											 \n"
		"{														 \n"
		"	col = vec4(1, 1, 1, texture(glyph, tex).a);			 \n"
		"}														 \n";

	_sh = shader::create(defaultvshader, defaultfshader);
	_sh.uniform("prj", ortho(0, window::size.x, 0, window::size.y));
}

void UI::render()
{
	static float lim = window::size.x - 50.f;
	glDisable(GL_DEPTH_TEST);
	_sh.use();
	_font.atlas.bind();
	for (text& text : _texts)
	{
		float x = text.pos.x;
		float y = text.pos.y;
		for (char c : text.str)
		{
			font::Char& C = _font.charmap[c];
			C.quad.bind();
			uniform("xform", x, text.pos.y, text.scale);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			if (x > lim)
			{
				x = text.pos.x;
				y -= _font.line;
			}
			else x += C.advance * text.scale;


		}
	}
}
void UI::renderText(const xfstr& text, float x, float y, float scale)
{
	static float lim = window::size.x - 50.f;

	_sh.use();
	_font.atlas.bind();
	float xx = x;
	float yy = y;
	for (char c : text)
	{
		font::Char& C = _font.charmap[c];
		C.quad.bind();
		uniform("xform", xx, yy, scale);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if (xx > window::size.x - 50.f)
		{
			xx = x;
			yy -= _font.line;
		}
		else xx += C.advance * scale;
	}
}