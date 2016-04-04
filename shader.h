#pragma once

#include <glload\gl_all.hpp>
#include <string>
#include <vector>

class Shader{
public:

	static GLuint createShader(GLenum shader_type, const std::string &shader_text);
	static GLuint createProgram(const std::vector<GLuint> &shader_list);

};