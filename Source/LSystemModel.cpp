#include "LSystemModel.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

using namespace glm;

#define PI (3.141592653589793)

LSystemModel::LSystemModel(std::string lSystemInput)
{
	float angle;// = arcAngle / numberOfEdges;
	//nEdges = numberOfEdges;
	//glm::vec3 normal = glm::vec3(1.0f,0.0f,0.0f);
	glm::vec3 binormal = glm::vec3(0.0f,1.0f,0.0f);

	std::vector<Vertex> mesh;
	//for (int k = 0; k <= numberOfEdges; k++){
		//angle = (radians(arcAngle) *k/ numberOfEdges) ;
		//mesh.push_back(Vertex(position + (normal * cos(angle) + binormal * sin(angle)) * radius1, glm::vec3(0.0f, 1.0f, 0.0f), color1));
		//mesh.push_back(Vertex(position + (normal * cos(angle) + binormal * sin(angle)) * radius2, glm::vec3(0.0f, 1.0f, 0.0f), color2));
	//}

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


LSystemModel::~LSystemModel()
{
}

void LSystemModel::Draw()
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
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (nEdges*2)+2); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}