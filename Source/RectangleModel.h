#pragma once
#include "C:\Users\Timu\Documents\371\comp371\Source\Model.h"

class RectangleModel :
	public Model
{
public:

	RectangleModel(glm::vec3 p1, glm::vec3 p2, glm::vec3 normal, float width, glm::vec3 color);
	~RectangleModel();

	 void Update(float dt);
	 void Draw();

protected:

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};

