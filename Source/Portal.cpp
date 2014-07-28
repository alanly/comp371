// \file Portal.cpp
// author: Tim Smith
//
// reference used : http://gamedev.stackexchange.com/questions/25596/opengl-create-tunnel-triangles-and-texture-coords-on-a-3d-path

#include "Portal.h"

#include "Renderer.h"
#include "ModelGroup.h"
#include "CubeModel.h"
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
	float angle;
	float a = 1.0f;//max for a float

	glm::vec3 tangent;
	glm::vec3 normal;
	glm::vec3 binormal;

	glm::vec3 direction;
	glm::vec3 dirnormal;
	glm::vec3 dirbinormal;

	sectors = inputPoints.size()-1;
	edges = edgeCount;

	std::vector<glm::vec3> tunnelPoint;
	//for each of the path vectors, create the appropriate 'ring'
	for(int j = 0; j < inputPoints.size(); j++)
	{

		//figure out the tangent - the direction of the tunnel at a given control point
		if(j==0){
			tangent = glm::vec3(inputPoints[j+1].x - inputPoints[j].x,
								inputPoints[j+1].y - inputPoints[j].y,
								inputPoints[j+1].z - inputPoints[j].z);
		}
		else if(j== inputPoints.size()-1)
		{
			tangent = glm::vec3(inputPoints[j].x - inputPoints[j-1].x, 
								inputPoints[j].y - inputPoints[j-1].y, 
								inputPoints[j].z - inputPoints[j-1].z);
		}
		else
		{
			tangent = glm::vec3(inputPoints[j+1].x - inputPoints[j-1].x, 
								inputPoints[j+1].y - inputPoints[j-1].y, 
								inputPoints[j+1].z - inputPoints[j-1].z);
		}
		//figure out the direction of the current segment
		if(j==0){
			direction = glm::vec3(inputPoints[j+1].x - inputPoints[j].x,
								inputPoints[j+1].y - inputPoints[j].y,
								inputPoints[j+1].z - inputPoints[j].z);
		}
		else if(j == inputPoints.size()-1)
		{
			direction = glm::vec3(inputPoints[j].x - inputPoints[j-1].x, 
								inputPoints[j].y - inputPoints[j-1].y, 
								inputPoints[j].z - inputPoints[j-1].z);
		}
		else
		{
			direction = glm::vec3(inputPoints[j+1].x - inputPoints[j].x, 
								inputPoints[j+1].y - inputPoints[j].y, 
								inputPoints[j+1].z - inputPoints[j].z);
		}

		tangent = glm::normalize(tangent);
		normal = glm::cross(upVector,tangent);
		binormal = glm::cross(tangent, normal);

		dirnormal = glm::cross(upVector,glm::normalize(direction));
		dirbinormal = glm::cross(glm::normalize(direction),dirnormal);

		for (int k = 0; k < edgeCount; k++) {// on each point, generate the ring
			angle = 2 * PI * k / edgeCount;
			tunnelPoint.push_back( inputPoints[j] + (normal * cos(angle) + binormal * sin(angle)) * radius );
			color = glm::vec3(1.0f);
			color.x = ((float)rand()/(float)(RAND_MAX)) * a;
			color.y = ((float)rand()/(float)(RAND_MAX)) * a;
			color.z = ((float)rand()/(float)(RAND_MAX)) * a;

			if(j!=inputPoints.size()-1){

			//////////
			//decals//
			/////////

			//begin hinge section
			CubeModel * c = new CubeModel(glm::vec3(0.05f,0.05f,0.05f));
			c->SetScaling(glm::vec3(8.0f,3.0f,10.0f));
			
			CubeModel * m = new CubeModel(glm::vec3(0.05f,0.05f,0.05f));
			m->SetRotation(binormal, degrees(atan(tangent.y/tangent.x ))); 
			m->SetPosition(inputPoints[j] + (normal * cos(angle) + binormal * sin(angle)) * radius * 0.9f);
			c->SetParent(m);
			c->SetRotation(glm::vec3(tangent.x, 0.0f,0.0f),degrees(angle));
			//end hinge section

			//begin stretch segment
			CubeModel * c2 = new CubeModel(glm::vec3(0.05f,0.05f,0.05f));
			c2->SetPosition(inputPoints[j]+direction/2.0f + (dirnormal * cos(angle) + dirbinormal * sin(angle)) * radius * 0.9f);
			
			glm::vec3 nextTangent;
			if(j==0){
				nextTangent = glm::vec3(inputPoints[j+2].x - inputPoints[j+1].x,
								inputPoints[j+2].y - inputPoints[j+1].y,
								inputPoints[j+2].z - inputPoints[j+1].z);
			}
			else if(j== inputPoints.size()-2)
			{
				nextTangent = glm::vec3(inputPoints[j+1].x - inputPoints[j].x, 
									inputPoints[j+1].y - inputPoints[j].y, 
									inputPoints[j+1].z - inputPoints[j].z);
			}
			else
			{
				nextTangent = glm::vec3(inputPoints[j+2].x - inputPoints[j].x, 
									inputPoints[j+2].y - inputPoints[j].y, 
									inputPoints[j+2].z - inputPoints[j].z);
			}

			
			nextTangent = glm::normalize(nextTangent);
			glm::vec3 nextNormal = glm::cross(upVector,nextTangent);
			glm::vec3 nextBinormal = glm::cross(nextTangent, nextNormal);

			glm::vec3 currentPoint(inputPoints[j] + (normal * cos(angle) + binormal * sin(angle)) * radius);
			glm::vec3 nextPoint(inputPoints[j+1] + (nextNormal * cos(angle) + nextBinormal * sin(angle)) * radius);

			float distance = glm::length(nextPoint-currentPoint);

			c2->SetScaling(glm::vec3(distance*19.0f,1.0f,1.0f));
			c2->SetRotation(dirbinormal, degrees(atan(direction.y/direction.x )));
			//end stretch segment


			decals.push_back(c);
			decals.push_back(c2);
			}
			///endDecals///
			vertexVector.push_back(Vertex(tunnelPoint.back(), binormal* cos(angle), color)); ///TODO fix the normal!
		}
	}

	const int size =  vertexVector.size()*6;
	Vertex * vertexBuffer = new Vertex [size];


	int i = 1;
	for(int j = 0; j<edgeCount*(inputPoints.size()-1)/*(edgeCount*(inputPoints.size()-2))/*((edgeCount*i)+edgeCount)*/; j++){
		//for(int j = 0; j<8; j++){
			if((j+1)%(edgeCount)==0 && j!=0){//next cylinder
				vertexBuffer[j*6] =     vertexVector[j];//i
				vertexBuffer[(j*6)+1] = vertexVector[j+edgeCount];
				vertexBuffer[(j*6)+2] = vertexVector[j+1];
				vertexBuffer[(j*6)+3] = vertexVector[j+1];
				vertexBuffer[(j*6)+4] = vertexVector[j];
				vertexBuffer[(j*6)+5] = vertexVector[j-edgeCount+1];
			}
			else{//normal case
				vertexBuffer[j*6]	  = vertexVector[j];
				vertexBuffer[(j*6)+1] = vertexVector[j+edgeCount];
				vertexBuffer[(j*6)+2] = vertexVector[j+edgeCount+1];
				vertexBuffer[(j*6)+3] = vertexVector[j+edgeCount+1];
				vertexBuffer[(j*6)+4] = vertexVector[j+1];
				vertexBuffer[(j*6)+5] = vertexVector[j];
			}



		}
	


	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer[0])*vertexVector.size()*6, vertexBuffer, GL_STATIC_DRAW);
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

	// Draw the triangles !  GL_TRIANGLE_STRIP		GL_LINE_STRIP
	glDrawArrays(GL_TRIANGLES, 0, edges*sectors*6); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	for(unsigned int i=0;i<decals.size();i++){
		decals[i]->Draw();
	}
}