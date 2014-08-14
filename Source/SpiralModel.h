#pragma once
#include "Model.h"
#include <vector>

class SpiralModel :
	public Model
{
public:
	SpiralModel(glm::vec4 color1,
		     glm::vec4 color2,
			 glm::vec3 position,
			 glm::vec3 upVector,
			 glm::vec3 binormal,
			 float radius1,
			 float radius2,
			 float arcAngle,
			 int numberOfEdges,
			 float height);
	~SpiralModel();

	virtual void Update(float dt);
	virtual void Draw();

protected:

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec4 color;

		Vertex() : position(glm::vec3(0.0f)),
					normal(glm::vec3(0.0f)),
					color(glm::vec4(1.0f))
		{}

		Vertex(glm::vec3 p, glm::vec3 n, glm::vec4 c) :position(p), normal(n), color(c)
		{}
	};
	unsigned int nEdges;
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	std::vector<Model *> m_vDoodads;

};

