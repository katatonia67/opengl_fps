#include <glload/gl_all.hpp>

#include <shader.h>

#include "map.h"

static const std::string vertex_shader =
	"#version 330\n"
	"in vec4 vertexPosition;\n"
	"in vec4 vertexColor;\n"
	"uniform mat4 obj_transform;\n"
	"out vec4 fragmentColor;\n"
	"void main()\n"
	"{\n"
	//"gl_Position = vec4(vertexPosition.x,vertexPosition.y, 0.0f, 1.0f);\n"
	"gl_Position = obj_transform*vertexPosition;\n"
	"fragmentColor = normalize(vertexColor);\n"
	"}\n";

static const std::string fragment_shader =
	"#version 330\n"
	"in vec4 fragmentColor;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = fragmentColor;\n"
	"}\n";

glm::mat4 Map::getTransformationMatrix() const{
	glm::mat4 matrix;
	matrix[3][0] = 0.2f;
	matrix[3][1] = 0.2f;
	matrix[3][2] = 0.2f;
	matrix[3][3] = 1.0f;
	return matrix;
}

void Map::init(){
	//create mesh
	_cached_mesh = std::unique_ptr<glmesh::Mesh>(buildMesh());
	//create shaders
	std::vector<GLuint> shader_list;
	shader_list.push_back(Shader::createShader(gl::VERTEX_SHADER, vertex_shader));
	shader_list.push_back(Shader::createShader(gl::FRAGMENT_SHADER, fragment_shader));
	_shader_program = Shader::createProgram(shader_list);
	std::for_each(shader_list.begin(), shader_list.end(), gl::DeleteShader);
}

void Map::draw(){
	GLuint obj_transform = gl::GetUniformLocation(_shader_program, "obj_transform");
	glm::mat4 obj_transform_matrix = getTransformationMatrix();
	gl::UseProgram(_shader_program);
	gl::UniformMatrix4fv(obj_transform, 1, gl::FALSE_, &obj_transform_matrix[0][0]);
	_cached_mesh->Render("all");
	gl::UseProgram(0);
}

glmesh::Mesh* Map::buildMesh(){
	//Create vertex format
	glmesh::AttributeList attribs;
	//position
	attribs.push_back(glmesh::AttribDesc(0, 4, glmesh::VDT_SINGLE_FLOAT, glmesh::ADT_FLOAT));
	//color
	attribs.push_back(glmesh::AttribDesc(1, 4, glmesh::VDT_UNSIGN_BYTE, glmesh::ADT_NORM_FLOAT));
	//vertex format from attributes
	glmesh::VertexFormat vfmt(attribs);

	//now use of CpuDateWriter to create our buffer
	glmesh::CpuDataWriter writer(vfmt, 4);

	{
		writer.Attrib(0.0f, 0.0f, 0.0f, 1.0f);
		writer.Attrib<GLubyte>(12, 0, 12, 255);
		writer.Attrib(0.5f, 0.0f, 0.0f, 1.0f);
		writer.Attrib<GLubyte>(13, 128, 64, 255);
		writer.Attrib(0.0f, 0.5f, 0.0f, 1.0f);
		writer.Attrib<GLubyte>(32, 0, 45, 255);
		writer.Attrib(0.5f, 0.5f, 0.0f, 1.0f);
		writer.Attrib<GLubyte>(0, 0, 255, 255);
	}

	GLuint buffer = writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW);

	//Create a mesh variant VAOs
	GLuint vao;

	gl::GenVertexArrays(1, &vao);

	gl::BindBuffer(gl::ARRAY_BUFFER, buffer);

	gl::BindVertexArray(vao);
	vfmt.BindAttributes(0);

	gl::BindBuffer(gl::ARRAY_BUFFER, 0);

	//shader variance
	glmesh::MeshVariantMap variants;
	variants["all"] = vao;

	glmesh::RenderCmdList cmd_list;
	cmd_list.DrawArrays(gl::TRIANGLE_STRIP, 0, 4);

	std::vector<GLuint> buffers(1, buffer);
	return new glmesh::Mesh(buffers, vao, cmd_list, variants);
}