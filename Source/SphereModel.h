//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include <vector>
#include <gl\glew.h>
class SphereModel : public Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	SphereModel(float radius, unsigned int rings, unsigned int sectors);
	virtual ~SphereModel();

	virtual void Update(float dt);
	virtual void Draw();

protected:

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};


	std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};
