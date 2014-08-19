/**
 * @author Louis McLean (spiral, bridge and image plane geometry)
 * @author Tiffany Ip (images)
 * @author Alan Ly (image sets and multiple-shader rendering)
 */

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
			 float height,
			 std::vector<CaptionImageSet*> images
			 )
			 : mImages(images)
{
	float angle;// = arcAngle / numberOfEdges;
	nEdges = numberOfEdges;
	
	float heightIncrement = (float)height/numberOfEdges; 
	glm::vec3 yComponent;
	std::vector<Vertex> mesh;
	float bridgeLength = 2.0f;
	float bridgeWidth = 1.0f; 

	mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/SolidColor.vertexshader", "../Source/Shaders/SolidColor.fragmentshader");
	GLuint imageShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Image.vertexshader", "../Source/Shaders/Image.fragmentshader");

	for (int k = 0; k <= numberOfEdges; k++)
	{
		angle = (radians(arcAngle) * k / numberOfEdges);
		yComponent = glm::vec3(0.f,heightIncrement*k,0.f);
		Vertex innerPoint(position + (upVector * cos(angle) + binormal * sin(angle)) * radius1 + yComponent, glm::vec3(0.0f, 1.0f, 0.0f), color1);
		mesh.push_back(innerPoint);
		Vertex outerPoint(position + (upVector * cos(angle) + binormal * sin(angle)) * radius2 + yComponent, glm::vec3(0.0f, 1.0f, 0.0f), color2); 
		mesh.push_back(outerPoint);

		//We will assume always having 25 stories, and as such, more than 25 edges to our spiral (25 reddit/stories per page)
		//ex. if numb. edges ==75, every 3 edges should have a bridge expanding out
		if( 0 == k % (numberOfEdges/25) )
		{
			//this goes from the outer radius of the point we just made, along the (i think) binormal to a range of wtv length you want the bridge to be.
			//rectangle bridges and any other decals we add can be put into a vector of decals that on the spiral classes' draw function iterates through the vector calling their respective draw()
			//At the end of the bridge, we'll construct an image from the CURL thing.
			glm::vec3 p1 = outerPoint.position;
			glm::vec3 bridgeDirection = outerPoint.position - innerPoint.position;
			glm::vec3 p2 = p1 + (bridgeDirection * bridgeLength);

			//Make a bridge
			m_vDoodads.push_back(new RectangleModel(p1, p2, glm::vec3(0.0f,1.0f,0.0f), bridgeWidth,glm::vec3(0.0f,1.0f,0.0f)));

			
			/************************************************************************/
			/* Create the image plane.                                              */
			/************************************************************************/

			// Calculate the rotation.
			glm::vec3 oldNormal(0.0f,0.0f,1.0f);
			glm::vec3 newNormal = normalize(-bridgeDirection);
			glm::vec3 rotationAxis = cross(oldNormal,newNormal);
			float rotationAngle = acos(dot(oldNormal, newNormal) / (length(oldNormal) * length(newNormal)));

			// Create the main image plane instance.
			PlaneModel* imagePlane = new PlaneModel(glm::vec3(1.f, 1.f, 1.f));
			
			// Set the image plane attributes,
			imagePlane->SetPosition(p2 + normalize(bridgeDirection) + glm::vec3(0.f, 1.f, 0.f));
			imagePlane->SetRotation(rotationAxis, degrees(rotationAngle));
			imagePlane->SetShader(imageShaderProgramID);

			// Choose an image,
			CaptionImageSet* img = mImages.at(rand() % mImages.size());
			imagePlane->SetImage(img->GetSubject());

			// Add the plane to the list,
			m_vDoodads.push_back(imagePlane);

			// Check if there's an associated caption,
			if (img->HasCaption())
			{
				// Create the caption image plane instance.
				PlaneModel* captionPlane = new PlaneModel(glm::vec3(1.f, 1.f, 1.f));

				// Set the image plane attributes,
				// We'll set the y += 2.f, to sit on top of our image.
				captionPlane->SetPosition(p2 + normalize(bridgeDirection) + glm::vec3(0.f, 2.f, 0.f));
				captionPlane->SetRotation(rotationAxis, degrees(rotationAngle));
				captionPlane->SetShader(imageShaderProgramID);

				// Get the caption image instance,
				captionPlane->SetImage(img->GetCaption());

				// Add the plane to the list,
				m_vDoodads.push_back(captionPlane);
			}
		}

		
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
}

void SpiralModel::DrawImages(Camera* currentCamera, unsigned int numOfLights, GLfloat* lightPositions, GLfloat* lightColors, GLfloat* lightCoefficients)
{
	for(int i = 0; i<m_vDoodads.size(); i++)
	{
		m_vDoodads[i]->PrepareDraw(currentCamera, numOfLights, lightPositions, lightColors, lightCoefficients);
		m_vDoodads[i]->Draw();
	}
}
