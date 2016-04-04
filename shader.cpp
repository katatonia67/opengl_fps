#include "shader.h"

//From shader text
GLuint Shader::createShader(GLenum shader_type, const std::string &shader_text){
	GLuint shader = gl::CreateShader(shader_type);
	const char *strFileData = shader_text.c_str();
	gl::ShaderSource(shader, 1, &strFileData, NULL);

	gl::CompileShader(shader);

	GLint status;
	gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
	if (status == gl::FALSE_){
		GLint infoLogLength;
		gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		gl::GetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(shader_type){
			case gl::VERTEX_SHADER: strShaderType = "vertex"; break;
			case gl::GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case gl::FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	return shader;
}

//create shader program
GLuint Shader::createProgram(const std::vector<GLuint> &shader_list){
	
	GLuint program = gl::CreateProgram();

	for(size_t iLoop = 0; iLoop < shader_list.size(); iLoop++)
		gl::AttachShader(program, shader_list[iLoop]);

	gl::LinkProgram(program);

	GLint status;
	gl::GetProgramiv (program, gl::LINK_STATUS, &status);
	if (status == gl::FALSE_)
	{
		GLint infoLogLength;
		gl::GetProgramiv(program, gl::INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		gl::GetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for(size_t iLoop = 0; iLoop < shader_list.size(); iLoop++)
		gl::DetachShader(program, shader_list[iLoop]);

	return program;	
}