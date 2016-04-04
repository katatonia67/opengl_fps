#pragma once
#include <glmesh\glmesh.h>
#include <glm\glm.hpp>

class Map{
	
public:

	void init();
	void draw();

private:

	///////////
	//members//
	///////////

	std::unique_ptr<glmesh::Mesh> _cached_mesh;
	GLuint _shader_program;

	//transformations
	glm::vec4 _translation;
	glm::vec4 _rotation;
	glm::vec4 _scale;

	/////////////
	//functions//
	/////////////

	glmesh::Mesh* buildMesh();
	glm::mat4 getTransformationMatrix() const;
};