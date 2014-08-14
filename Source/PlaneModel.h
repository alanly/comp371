#pragma once

#include "Model.h"

class PlaneModel : public Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	PlaneModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~PlaneModel();

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
        glm::vec2 texCoords;
	};

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};
