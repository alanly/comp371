//Written by Thomas Rahn


#pragma once

#include "Model.h"
#define GLEW_STATIC
#include <GL/glew.h>

class BlenderModel : public Model
{
public:
	BlenderModel(const char * path, const char * texturePath);
	virtual ~BlenderModel();

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
	unsigned int numVertices;
	GLuint texture;
	GLuint textureID;

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	unsigned int mNormalBufferID;
	unsigned int mUVBufferID;

};
