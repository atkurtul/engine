#include "window.h"
#include "vertex_array.h"
#include "buffer.h"
#include "shader.h"
#include "UI.h"
#include "cam.h"
#include "clock.h"

using vecf = xfvec<float>;
using vecu = xfvec<uint>;
using veci = xfvec<int>;
using vecv2 = xfvec<vec2>;
using vecv3 = xfvec<vec3>;
using vecv2u = xfvec<uvec2>;
using vecv3u = xfvec<uvec3>;
using vecv2i = xfvec<ivec2>;
using vecv3i = xfvec<ivec3>;

int main()
{
	window::init(1280, 720);
	//shader main("main.vert", "main.frag");
	vecf verts = { 0, 0, 1, 0, 0, 1, 1, 1 };
	vao vao;
	vao.gen();
	buffer(verts);
	vao.attrib(0, 2);

	UI ui("consolas.fnt");
	while (window::runs())
	{
		//main.use();
		//vao.bind();
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		ui.renderText(tostr(clock::fps), 0, 150);
		ui.renderText("Hello World!", 0, 100);
	}
}