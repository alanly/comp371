#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Model.h"
#include <vector>
#include <string>
#include "SOIL.h"
#include "UTFConvert.h"

class PlaneModel : public Model
{
public:
	PlaneModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~PlaneModel();

	void Update(float dt);
	void Draw();

	void SetImage(const char* image);

private:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
        glm::vec2 texCoords;
	};

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	GLuint tex;
	unsigned char* pImage;
	int pImageWidth;
	int pImageHeight;

	bool hasImage;
};
