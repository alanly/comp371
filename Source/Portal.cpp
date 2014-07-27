// \file Portal.cpp
// author: Tim Smith
//
// reference used : http://gamedev.stackexchange.com/questions/25596/opengl-create-tunnel-triangles-and-texture-coords-on-a-3d-path

#include "Portal.h"

#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#define PI (3.141592653589793)

using namespace glm;

void Portal::Update(float dt){};

//Always insert at least 2 points
Portal::Portal(std::vector<glm::vec3> inputPoints, float radius, int edgeCount)
{
	glm::vec3 upVector = glm::vec3(0.0f,0.0f,1.0f);
	glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.0f);
	std::vector<Vertex> vertexVector;
	float angle;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 binormal;

	std::vector<glm::vec3> tunnelPoint;
	//for each of the path vectors, create the appropriate 'ring'
	for(int j = 0; j < inputPoints.size(); j++)
	{

		//figure out the tangent - the direction of the tunnel at a given control point
		if(j==0){
			tangent = glm::vec3(inputPoints[j].x - inputPoints[j+1].x,
								inputPoints[j].y - inputPoints[j+1].y,
								inputPoints[j].z - inputPoints[j+1].z);
		}
		else if(j== inputPoints.size()-1)
		{
			tangent = glm::vec3(inputPoints[j-1].x - inputPoints[j].x, 
								inputPoints[j-1].y - inputPoints[j].y, 
								inputPoints[j-1].z - inputPoints[j].z);
		}
		else
		{
			tangent = glm::vec3(inputPoints[j-1].x - inputPoints[j+1].x, 
								inputPoints[j-1].y - inputPoints[j+1].y, 
								inputPoints[j-1].z - inputPoints[j+1].z);
		}

		normal = glm::cross(tangent,upVector);

		binormal = glm::cross(tangent, normal);

		for (int k = 0; k < edgeCount; k++) {// on each point, generate the ring
			angle = 2 * PI * k / edgeCount;
			tunnelPoint.push_back( inputPoints[j] + (normal * cos(angle) + binormal * sin(angle)) * radius );
			vertexVector.push_back(Vertex(tunnelPoint.back(), normal, color)); ///TODO fix the normal!
		}
	}

	
	Vertex* vertexBuffer = &vertexVector[0];//*[tunnelPoint.size()];
	
	
//	= {	  // position,								 normal,                  color
//								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) }, //left - red
//								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
//								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
//	};

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
}

Portal::~Portal()
{
}

void Portal::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
	
	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	0,				// attribute. No particular reason for 0, but must match the layout in the shader.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							sizeof(Vertex), // stride
							(void*)0        // array buffer offset
						);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	1,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
						);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	2,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
						);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}