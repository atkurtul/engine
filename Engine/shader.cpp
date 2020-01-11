#include "shader.h"
#include "glad/glad.h"

uint shader::compile(const char* path, int type)
{
	xfstr code;
	uint shader = glCreateShader(type);
	glShaderSource(shader, 1, code.read(path).ptr(), NULL);
	glCompileShader(shader);
	status(shader);
	return shader;
}

uint shader::compile_str(const char* str, int type)
{
	uint shader = glCreateShader(type);
	glShaderSource(shader, 1, &str, NULL);
	glCompileShader(shader);
	status(shader);
	return shader;
}

void shader::status(uint shaderID)
{
	int infolen, res;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &res);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infolen);
	xfstr err(infolen);
	glGetShaderInfoLog(shaderID, infolen, NULL, err.data());
	if (infolen) std::cout << err;
}

void shader::pstatus(uint ID)
{
	int infolen, res;
	glGetProgramiv(ID, GL_COMPILE_STATUS, &res);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infolen);
	xfstr err(infolen);
	glGetShaderInfoLog(ID, infolen, NULL, err.data());
	if (infolen) std::cout << err;
}

shader::shader(const char* cs_path)
{
	_id = glCreateProgram();
	glAttachShader(_id, compile(cs_path, GL_COMPUTE_SHADER));
	glLinkProgram(_id);
	glUseProgram(_id);
	pstatus(_id);
}

shader::shader(const char* vs_path, const char* fs_path)
{
	active = _id;
	_id = glCreateProgram();
	glAttachShader(_id, compile(vs_path, GL_VERTEX_SHADER));
	glAttachShader(_id, compile(fs_path, GL_FRAGMENT_SHADER));
	glLinkProgram(_id);
	glUseProgram(_id);
	pstatus(_id);
}

shader::shader()
	: _id(-1)
{
}

shader::shader(const shader& s) 
	: _id(s._id)
{
}

shader::shader(uint id) 
	: _id(id)
{
}

shader& shader::operator=(const shader& s)
{
	_id = s._id;
	return *this;
}

shader shader::create(const char* vs, const char* fs)
{
	uint re;
	re = glCreateProgram();
	glAttachShader(re, compile_str(vs, GL_VERTEX_SHADER));
	glAttachShader(re, compile_str(fs, GL_FRAGMENT_SHADER));
	glLinkProgram(re);
	glUseProgram(re);
	active = re;
	pstatus(re);
	return re;
}


void shader::use()
{
	glUseProgram(active = _id);
}

shader::operator uint() const
{
	return _id;
}

void shader::uniform(const char* uni, const vec2& v)
{
	glUniform2fv(glGetUniformLocation(_id, uni), 1, v.data);
}

void shader::uniform(const char* uni, const vec3& v)
{
	glUniform3fv(glGetUniformLocation(_id, uni), 1, v.data);
}

void shader::uniform(const char* uni, const vec4& v)
{
	glUniform4fv(glGetUniformLocation(_id, uni), 1, v.data);
}

void shader::uniform(const char* uni, const mat2& m)
{
	glUniformMatrix2fv(glGetUniformLocation(_id, uni), 1, 0, m.data);
}

void shader::uniform(const char* uni, const mat3& m)
{
	glUniformMatrix3fv(glGetUniformLocation(_id, uni), 1, 0, m.data);
}

void shader::uniform(const char* uni, const mat4& m)
{
	glUniformMatrix4fv(glGetUniformLocation(_id, uni), 1, 0, m.data);
}

void shader::uniform(const char* uni, const xfvec<vec2>& v)
{
	glUniform2fv(glGetUniformLocation(_id, uni), v.size(), (float*)v.data());
}

void shader::uniform(const char* uni, const xfvec<vec3>& v)
{
	glUniform3fv(glGetUniformLocation(_id, uni), v.size(), (float*)v.data());
}

void shader::uniform(const char* uni, const xfvec<vec4>& v)
{
	glUniform4fv(glGetUniformLocation(_id, uni), v.size(), (float*)v.data());
}

void shader::uniform(const char* uni, const xfvec<mat2>& v)
{
	glUniformMatrix2fv(glGetUniformLocation(_id, uni), v.size(), 0, (float*)v.data());
}

void shader::uniform(const char* uni, const xfvec<mat3>& v)
{
	glUniformMatrix3fv(glGetUniformLocation(_id, uni), v.size(), 0, (float*)v.data());
}

void shader::uniform(const char* uni, const xfvec<mat4>& v)
{
	glUniformMatrix4fv(glGetUniformLocation(_id, uni), v.size(), 0, (float*)v.data());
}

void shader::uniform(const char* uni, float x)
{
	glUniform1f(glGetUniformLocation(_id, uni), x);
}

void shader::uniform(const char* uni, int x)
{
	glUniform1i(glGetUniformLocation(_id, uni), x);
}

void shader::uniform(const char* uni, uint x)
{
	glUniform1ui(glGetUniformLocation(_id, uni), x);
}

void shader::uniform(const char* uni, float x, float y)
{
	glUniform2f(glGetUniformLocation(_id, uni), x, y);
}

void shader::uniform(const char* uni, int x, int y)
{
	glUniform2i(glGetUniformLocation(_id, uni), x, y);
}

void shader::uniform(const char* uni, uint x, uint y)
{
	glUniform2ui(glGetUniformLocation(_id, uni), x, y);
}

void shader::uniform(const char* uni, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(_id, uni), x, y, z);
}

void shader::uniform(const char* uni, int x, int y, int z)
{
	glUniform3i(glGetUniformLocation(_id, uni), x, y, z);
}

void shader::uniform(const char* uni, uint x, uint y, uint z)
{
	glUniform3ui(glGetUniformLocation(_id, uni), x, y, z);
}

void shader::uniform(const char* uni, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(_id, uni), x, y, z, w);
}

void shader::uniform(const char* uni, int x, int y, int z, int w)
{
	glUniform4i(glGetUniformLocation(_id, uni), x, y, z, w);
}

void shader::uniform(const char* uni, uint x, uint y, uint z, uint w)
{
	glUniform4ui(glGetUniformLocation(_id, uni), x, y, z, w);
}