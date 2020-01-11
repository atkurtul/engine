#include "window.h"
#include "vertex_array.h"
#include "buffer.h"
#include "shader.h"
#include "UI.h"
#include "cam.h"
#include "clock.h"
#include "mouse.h"
#include "input.h"
#include "obj_loader.h"

using vecf = xfvec<float>;
using vecu = xfvec<uint>;
using veci = xfvec<int>;
using vecv2 = xfvec<vec2>;
using vecv3 = xfvec<vec3>;
using vecv2u = xfvec<uvec2>;
using vecv3u = xfvec<uvec3>;
using vecv2i = xfvec<ivec2>;
using vecv3i = xfvec<ivec3>;

struct light
{
	mat4 view;
	dvec3& right = view.col[0].xyz;
	dvec3& up = view.col[1].xyz;
	dvec3& dir = view.col[2].xyz;
	vec3 pos = vec3(5, 75, -10);

	light()
	{
		dir = -pos.norm();
		up = cross(dir, right);
	}

	void update()
	{
		mat4 y = roty(clock::dt);
		right = right * y;
		up = up * y;
		dir = dir * y;
		pos = pos * y;
		view.row[3].xyz = -pos * view;
	}
};

float near = 1.f, far = 300.f;
float orth = 250.f;
mat4 lightPrj = ortho(-orth, orth, -orth, orth, near, far);
const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
void genFBO(uint* fbo, uint* dm) {
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	*fbo = depthMapFBO;
	*dm = depthMap;
}

void collide(xfvec<mat4>& arr, xfvec<vec3>& vel, xfvec<mat3>& ang)
{
	static float elasticity = 0.98f;
	for (int i = 0; i < arr.size(); ++i)
	{
		vec3& pos = (vec3&)arr[i].row[3].xyz;
		for (int j = i + 1; j < arr.size(); ++j)
		{
			vec3 collision = pos - arr[j].row[3].xyz;
			float distance = collision.len();
			if (distance <= 2.f)
			{
				pos += collision * 0.5f * (2.f - distance);
				arr[j].row[3].xyz -= collision * 0.5f * (2.f - distance);
				vec3 temp = vel[i];
				vel[i] = vel[j] * elasticity;
				vel[j] = temp * elasticity;
				//vel[i] = (vel[j] * 0.95f + vel[i] * 0.05f) * elasticity;
				//vel[j] = (vel[j] * 0.05f + temp * 0.95f) * elasticity;
			}
		}
		vec3 force = vec3(0, 5, 0) - pos;
		vel[i] += force.norm() / force.len() * clock::dt * 12.f;
		vel[i].y -= clock::dt * 4.f;
		arr[i].row[3].xyz += vel[i] * clock::dt * 2.f;
		arr[i].row[0].xyz = arr[i].row[0].xyz * ang[i];
		arr[i].row[1].xyz = arr[i].row[1].xyz * ang[i];
		arr[i].row[2].xyz = arr[i].row[2].xyz * ang[i];
		if (pos.y <= -1.f)  pos.y = -1.f, vel[i].y *= -elasticity;
		if (absl(pos.x) >= 50.f) pos.x = sign(pos.x) * 49.99f, vel[i].x *= -elasticity;
		if (absl(pos.z) >= 50.f) pos.z = sign(pos.z) * 49.99f, vel[i].z *= -elasticity;
	}
}

int main()
{
	window::init(1600, 900);
	mat4 prj = perspective(90.f, window::size.y / window::size.x, 0.1f, 1000.f);
	shader main("shader.vert", "shader.frag");
	main.uniform("prj", prj);
	main.uniform("lightPrj", lightPrj);
	shader simple("simple.vert", "simple.frag");
	simple.uniform("prj", prj);
	UI ui("consolas.fnt");
	shader debug("debug.vert", "debug.frag");
	shader shadow("shadow.vert", "shadow.frag");
	shadow.uniform("prj", lightPrj);
	vao cube = obj_loader()("sphere.obj");
	vao plane = obj_loader()("plane.obj", 0.4);
	cam cam;
	light light;
	mice::hide();

	mat4 m2; m2.row[3].xz = 3;
	mat4 m3; m3.row[3].y = 5;

	uint fbo, dm;
	genFBO(&fbo, &dm);

	vao ray;
	ray.gen();
	uint rayvbo = buffer(xfvec<vec3>{5, 0});
	ray.attrib(0, 3, 0, 0);

	texture ground("ground.jpg");
	texture tex("jupi.jpg");

	xfvec<mat4> buff;
	xfvec<vec3> vs;
	xfvec<mat3> ang;
	int n = 0;

	while (window::runs())
	{
		++n;
		mat4 cview = cam.view;
		if (input(key::SPACE)) cview = light.view;
		main.use();
		cam.update();
		light.update();
		main.uniform("view", cview);
		main.uniform("lightView", light.view);
		main.uniform("lpos", light.pos);
		main.uniform("vpos", cam.pos);


		if (buff.size() > 200)
		{
			buff.erase(buff.begin(), buff.begin() + 200 - buff.size());
			vs.erase(vs.begin(), vs.begin() + 200 - vs.size());
		}
		static float t1 = 0.f, t2 = 0.f;
		t1 -= clock::dt;
		t2 -= clock::dt;
		collide(buff, vs, ang);
		//if (t1 <= 0.f) t1 = 0.02f, collide(buff, vs);
		if (input(key::Left) && t2 < 0.f)
		{
			t2 = 0.2f;
			mat4 m = axang(ranf(), ranf(), ranf(), ranf() * ct::pi);
			m.row[3].xyz = cam.pos - cam.dir * 4.f;
			buff.push(m);
			vs.push(cam.dir * -8.f);
			ang.push(axang(ranf(), ranf(), ranf(), 0.1f));
		}
		if (input(key::Right)) {
			mat4 m = axang(ranf(), ranf(), ranf(), ranf() * ct::pi);
			m.row[3].xyz = cam.pos - cam.dir * 4.f;
			buff.push(m);
			vs.push(cam.dir * -8.f);
			ang.push(axang(ranf(), ranf(), ranf(), 0.1f));
		}
		{
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_DEPTH_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE0);
			shadow.use();
			shadow.uniform("view", light.view);

			cube.bind();
			uniform("xform", buff);
			glDrawArraysInstanced(GL_TRIANGLES, 0, cube.size, buff.size());

			uniform("xform", m4id);
			plane.bind();
			glDrawArrays(GL_TRIANGLES, 0, plane.size);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, int(window::size.x), int(window::size.y));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, dm);
		}


		if (0)
		{
			debug.use();
			debug.uniform("near", near);
			debug.uniform("far", far);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, dm);
			//renderQuad();
		}

		else
		{
			main.use();
			glActiveTexture(GL_TEXTURE1);
			tex.bind();
			cube.bind();
			uniform("xform", buff);
			glDrawArraysInstanced(GL_TRIANGLES, 0, cube.size, buff.size());

			mat4 m4; m4.row[3].xyz = light.pos;
			uniform("xform", m4);
			glDrawArrays(GL_TRIANGLES, 0, cube.size);

			glActiveTexture(GL_TEXTURE1);
			ground.bind();
			uniform("xform", m4id);
			plane.bind();
			glDrawArrays(GL_TRIANGLES, 0, plane.size);

			simple.use();
			simple.uniform("view", cam.view);
			ray.bind();
			glBindBuffer(GL_ARRAY_BUFFER, rayvbo);
			vec3 arrray[2] = { cam.pos, 0 };
			glBufferSubData(GL_ARRAY_BUFFER, 0, 24, arrray[0].data);
			glDrawArrays(GL_LINE_STRIP, 0, 2);
		}

		static float t3 = 0.f;
		static int c = 0;
		static float fps = 0.f;
		++c;
		fps += clock::dt;
		t3 -= clock::dt;
		if (t3 <= 0.f) t3 = 0.2f, fps = 0.f, c = 0;

		glActiveTexture(GL_TEXTURE0);
		glDisable(GL_DEPTH_TEST);
		ui.renderText(tostr(c / fps), 0, 0);
		ui.renderText(tostr(buff.size()), window::size.x * 0.9f, 0);
		glEnable(GL_DEPTH_TEST);
	}
}

//int main()
//{
//	window::init(1280, 720);
//	//shader main("main.vert", "main.frag");
//	vecf verts = { 0, 0, 1, 0, 0, 1, 1, 1 };
//	vao vao;
//	vao.gen();
//	buffer(verts);
//	vao.attrib(0, 2);
//
//	UI ui("consolas.fnt");
//	while (window::runs())
//	{
//		//main.use();
//		//vao.bind();
//		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//		ui.renderText(tostr(clock::fps), 0, 150);
//		ui.renderText("Hello World!", 0, 100);
//	}
//}