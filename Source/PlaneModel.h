/************************************************************************/
/* @author Tiffany Ip                                                                     */
/************************************************************************/

#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Model.h"
#include <vector>
#include <string>
#include "UTFConvert.h"
#include "Image.h"

class PlaneModel : public Model
{
public:
	PlaneModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~PlaneModel();

	void Update(float dt);
	void Draw();

	void SetImage(Image* image);

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
	Image* image;
};
