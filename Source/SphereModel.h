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
	
	SphereModel(glm::vec3 Origin, float radius, unsigned int nRings, unsigned int nSectors, glm::vec4 color);
	virtual ~SphereModel();

	void Display();

	 void Update(float dt);
	 //void OverloadedDraw(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	 virtual void Draw();


protected:

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec4 color;

		Vertex(glm::vec3 p, glm::vec3 n, glm::vec4 c) :position(p), normal(n), color(c){}
		Vertex() : position(glm::vec3(0.0f)), 
                         normal(glm::vec3(0.0f)), 
						 color(glm::vec4(1.0f)){}
	};

	glm::vec3 tempVec;
	std::vector<Vertex> m_vertices;
 
	int numVertex;
	
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};
