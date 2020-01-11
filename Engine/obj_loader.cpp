#include "obj_loader.h"

vao obj_loader::operator()(const char* path, vec3 col)
{
	std::ifstream s;
	s.open(path);
	if (s.is_open()) std::cout << path << " obj file is open\n";
	else std::cout << "cant open obj file : " << path << "\n";
	xfstr code;
	xfstr sub;
	vec3 v;
	xfvec<vec3> vertices;
	xfvec<vec3> normals;
	xfvec<vec2> textures;
	xfvec<uvec3> indices;
	while (code.getline(s)) {
		sub = code.substr(0, 2);
		if (sub == "v ") {
			code.substr(2) >> v.x >> v.y >> v.z;
			vertices.push(v);

		}
		if (sub == "vt") {
			code.substr(3) >> v.x >> v.y;
			textures.push(v.xy);
		}
		if (sub == "vn") {
			code.substr(3) >> v.x >> v.y >> v.z;
			normals.push(v);
		}
		if (sub == "f ") {
			xfstr ssub = code.substr(2);
			while (ssub.find('/')) {
				uvec3 uv;
				ssub >> uv.x; --uv.x;
				ssub.erase(ssub.begin());
				ssub >> uv.y; --uv.y;
				ssub.erase(ssub.begin());
				ssub >> uv.z; --uv.z;
				indices.push(uv);
			}
		}
	}
	s.close();

	struct layout {
		vec3 v, n;
		vec2 t;
		vec3 c;
	};
	xfvec<layout> is;
	is.resize(indices.size());
	if (is0(col.len()))
	{
		for (uint i = 0; i < indices.size(); ++i) {
			is[i] =
			{
				vertices[indices[i].x],
				normals[indices[i].z],
				textures[indices[i].y],
				vertices[indices[i].x]
			};
		}
	}
	else
	{
		for (uint i = 0; i < indices.size(); ++i) {
			is[i] =
			{
				vertices[indices[i].x],
				normals[indices[i].z],
				textures[indices[i].y],
				col
			};
		}
	}
	vao vao;
	vao.gen();
	buffer(is, GL_ARRAY_BUFFER);
	vao.attrib(0, 3, 11, 0);
	vao.attrib(1, 3, 11, 3);
	vao.attrib(2, 2, 11, 6);
	vao.attrib(3, 3, 11, 8);
	vao.size = is.size();
	return vao;
}
