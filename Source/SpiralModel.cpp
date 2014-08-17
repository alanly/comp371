#pragma once

#include "SpiralModel.h"
#include "RectangleModel.h"
#include "PlaneModel.h"
#include "ArcModel.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <math.h>

using namespace glm;

SpiralModel::SpiralModel(glm::vec4 color1,
		     glm::vec4 color2,
			 glm::vec3 position,
			 glm::vec3 upVector,
			 glm::vec3 binormal,
			 float radius1,
			 float radius2,
			 float arcAngle,
			 int numberOfEdges,
			 float height)
{
	float angle;// = arcAngle / numberOfEdges;
	nEdges = numberOfEdges;
	
	float heightIncrement = (float)height/numberOfEdges; // yo this is the height
	glm::vec3 yComponent;
	std::vector<Vertex> mesh;
	float bridgeLength = 2.0f; // ARBITRARY YAY
	float bridgeWidth = 1.0f; // bridge is pencil dick

	mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Image.vertexshader", "../Source/Shaders/Image.fragmentshader");

	// Declare our images
	std::vector<const char*>* images = new std::vector<const char*>();
	images->push_back("gerlic.jpg");
	images->push_back("entertained.jpg");

	for (int k = 0; k <= numberOfEdges; k++)
	{
		angle = (radians(arcAngle) * k / numberOfEdges);
		yComponent = glm::vec3(0.f,heightIncrement*k,0.f);
		Vertex innerPoint(position + (upVector * cos(angle) + binormal * sin(angle)) * radius1 + yComponent, glm::vec3(0.0f, 1.0f, 0.0f), color1);
		mesh.push_back(innerPoint);
		Vertex outerPoint(position + (upVector * cos(angle) + binormal * sin(angle)) * radius2 + yComponent, glm::vec3(0.0f, 1.0f, 0.0f), color2); 
		mesh.push_back(outerPoint);

		//We will assume always having 25 stories, and as such, more than 25 edges to our spiral (25 reddit/stories per page)
		if( 0 == k % (numberOfEdges/25) )
		{//ex. if numb. edges ==75, every 3 edges should have a bridge expanding out
			//RectangleModel * r = new RectangleModel()//this goes from the outer radius of the point we just made, along the (i think) binormal to a range of wtv length you want the bridge to be.
													//If that doesnt work, try the normal.
			//rectangle bridges and any other decals we add can be put into a vector of decals that on the spiral classes' draw function iterates through the vector calling their respective draw()
			//At the end of the bridge, we'll construct an image from the CURL thing.
			glm::vec3 p1 = outerPoint.position;
			glm::vec3 bridgeDirection = outerPoint.position - innerPoint.position;
			glm::vec3 p2 = p1 + (bridgeDirection * bridgeLength);

			m_vDoodads.push_back(new RectangleModel(p1, p2, glm::vec3(0.0f,1.0f,0.0f), bridgeWidth,glm::vec3(0.0f,1.0f,0.0f)));

			//Portal entrance placeholder
			//m_vDoodads.push_back(new ArcModel(glm::vec4(0.0f,1.0f,0.0f,1.0f),glm::vec4(0.0f,0.0f,0.0f,1.0f),p2+glm::vec3(0.0f,1.0f,0.0f), cross(normalize(bridgeDirection),glm::vec3(0.0f,1.0f,0.0f)),glm::vec3(0.0f,1.0f,0.0f),0.0f,1.0f,360.0f,100));

			PlaneModel* pPlaneModel = new PlaneModel(glm::vec3(1.0f,1.0f,1.0f));
			pPlaneModel->SetPosition(p2+normalize(bridgeDirection)+glm::vec3(0.0f,1.0f,0.0f));
			glm::vec3 oldNormal(0.0f,0.0f,1.0f);
			glm::vec3 newNormal = normalize(-bridgeDirection);
			glm::vec3 rotationAxis = cross(oldNormal,newNormal);
			float rotationAngle = acos(dot(oldNormal, newNormal) / (length(oldNormal) * length(newNormal)));
			pPlaneModel->SetRotation(rotationAxis,degrees(rotationAngle));
			pPlaneModel->SetImage(images->at(rand() % images->size()));
			m_vDoodads.push_back(pPlaneModel);
		}

		//Make a bridge
	}

	const int size = mesh.size();
	Vertex * vertexBuffer = new Vertex[size];

	for (int i = 0; i < size; i++)
		vertexBuffer[i] = mesh[i];

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh[0])*mesh.size(), vertexBuffer, GL_STATIC_DRAW);
}

SpiralModel::~SpiralModel(void)
{
}

void SpiralModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
//	mRotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	//mRotationAngleInDegrees += 5.0f*dt;
}

void SpiralModel::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(mShaderProgramID, "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
		);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3)) // Color is Offsetted by 2 vec3 (see class Vertex)
		);

	// Draw the triangles !  GL_TRIANGLE_STRIP		GL_LINE_STRIP
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (nEdges*2)+2); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	for(int i = 0; i<m_vDoodads.size(); i++)
	{
		m_vDoodads[i]->SetShader(mShaderProgramID);
		m_vDoodads[i]->Draw();
	}
}


