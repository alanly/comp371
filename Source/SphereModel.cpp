//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "SphereModel.h"
#include "Renderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>

//include GLFW
#include <GLFW/glfw3.h>


// Include GLEW - OpenGL Extension Wrangler
#define GLEW_STATIC
#include <GL/glew.h>
#include <cmath>
#include <ctime>



#define M_PI 3.14159265359
#define M_PI_2 (3.14159265359/2.0f)
#define vecDown (0.f, -1.f, 0.f)
#define degToRad (M_PI/180)


using namespace glm;
using namespace std;



SphereModel::SphereModel(glm::vec3 Origin, float radius, unsigned int nRings, unsigned int nSectors, glm::vec4 color)
{

	float sectorAngle = (360)/nSectors;

	std::vector<Vertex> sphereMesh;

	
	

	float ringIncrement = (radius*2)/nRings;

	sphereMesh.push_back(Vertex((Origin-glm::vec3(0.f,radius,0.f)),
											normalize(Origin-glm::vec3(0.f,radius,0.f)),
											color));
	

	for(int n=1; n < nRings; n++)
	{

		
			//ring is height of current ring
			glm::vec3 ring = (Origin - radius*vecDown + (-ringIncrement * vecDown *n));
			float height = Origin.y - radius + (ringIncrement*n);
			
			float theta = glm::asin(height/radius); //height replaced length(ring)
			float newRadius = radius*(cos(theta));

			//this is where the loop goes to find the points (x points/ circle, each of which will correlate together to make a sector)
			for(int j=0; j<nSectors; j++)
			{
				float x = (float)((newRadius * glm::cos(j*sectorAngle*degToRad)) + (ring.x));
				float z = (float)(newRadius * glm::sin(j*sectorAngle*degToRad) + (ring.z));

				glm::vec3 tempVec(x, height, z);

				Vertex* v;

				float r = static_cast <float> (rand())/static_cast <float> (RAND_MAX);
	
				float r2 = static_cast <float> (rand())/static_cast <float> (RAND_MAX);
	
				float r3 = static_cast <float> (rand())/static_cast <float> (RAND_MAX);



				color = glm::vec4(r, r2, r3, 1);

				sphereMesh.push_back(Vertex(tempVec,
											glm::vec3(normalize(tempVec-Origin)),
											color));

			}

	}

	sphereMesh.push_back(Vertex((Origin+glm::vec3(0.f,radius,0.f)),
											normalize(Origin+(0.f,radius,0.f)),
											color));


	std::vector<Vertex*> finalLoop;

	


	//bottom fan = 0,1,2,2,0,3
	//0,1,2,2,3,4,0

	for(int i=1; i<=nSectors;i++) //loop first fan
	{
		if(i==1)
		{
			finalLoop.push_back(&sphereMesh[i-1]);
			finalLoop.push_back(&sphereMesh[i]);
			finalLoop.push_back(&sphereMesh[i+1]);
		}
		
		else
		{
			finalLoop.push_back(&sphereMesh[i]);
			finalLoop.push_back(&sphereMesh[0]);
			finalLoop.push_back(&sphereMesh[(i % nSectors)+1]);

		}

		//read from spheremesh, push back to final loop
	}

	for(int i=1; i<nRings-1 ;i++) //loop for body 
	{
		

		for(int j=1; j<=nSectors+1;j++)
		{
			if(j==nSectors+1)
			{
			finalLoop.push_back(&sphereMesh[1 + ((i-1)*nSectors)]);
			finalLoop.push_back(&sphereMesh[1 + ((i)*nSectors)]);

			//finalLoop.push_back(&sphereMesh[1 + ((i+1)*nSectors)]);
			//finalLoop.push_back(&sphereMesh[1 + (i*nSectors)]);
			}

			else
			{
			finalLoop.push_back(&sphereMesh[j + ((i-1)*nSectors)]);
			finalLoop.push_back(&sphereMesh[j + ((i)*nSectors)]);
			}
		
		}


	}

	int back = sphereMesh.size()-1;
	for(int i=sphereMesh.size()-nSectors; i<sphereMesh.size()-1; i++) //loop for top fan
	{
		if(i==sphereMesh.size()-nSectors)
		{

			finalLoop.push_back(&sphereMesh[i-1]);
		
		}

			//finalLoop.push_back(&sphereMesh[i]);
			finalLoop.push_back(&sphereMesh[i]);
			finalLoop.push_back(&sphereMesh[back]);
			finalLoop.push_back(&sphereMesh[i+1]);
			//finalLoop.push_back(&sphereMesh[i+1]);

			
			//finalLoop.push_back(&sphereMesh[i-nSectors]);
				
			
			
			
		


			



	}



	//build dynamic vertex aka build new vertex to correct the order of the previous vertex vector



	const int size = finalLoop.size(); //sphereMesh.size();
	Vertex *vertexBuffer = new Vertex[size];
			
	for(int i=0; i<size;i++)
	{
		//spheremesh must be put in to show the sphere without the outer filling
		vertexBuffer[i] = *finalLoop[i]; //sphereMesh[i];
	}

	//finalLoop.size() should be the value to put in for the drawing
	//sphereMesh.size() placed here shows the sphere without outer filling

	numVertex = finalLoop.size()*2;  //sphereMesh.size(); //2*nSectors*nRings + nSectors*2;
			
			

	//Create a vertex array 
	glGenVertexArrays(1, &mVertexArrayID); 
 
	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID) 
	glGenBuffers(1, &mVertexBufferID); 
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphereMesh[0])*finalLoop.size(), vertexBuffer, GL_STATIC_DRAW);//(sphereMesh[0])*sphereMesh.size(), vertexBuffer, GL_STATIC_DRAW);
	//^THIS COCKSUCKER FUCKIGN HIDDEN FUNCTION, MADE ME AND TIM SPEND 3 HOURS TRYING TO FIGURE OUT WHY ONLY A BOWL WASNT DRAWING


} 

SphereModel::~SphereModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void SphereModel::Update(float dt)
{
	// If you are curious, uncomment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
}
void SphereModel::Draw()
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
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertex); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

}
