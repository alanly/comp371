//Portal header
//Author: Tim Smith

#pragma once
#include <vector>
#include "Model.h"

class Portal : public Model
{
public:
	//Portal();
	Portal(std::vector<glm::vec3> inputPoints, float radius, int edgeCount);
	~Portal();

	virtual void Update(float dt);
	void Draw();

private:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;

		Vertex(){
			position = glm::vec3(0.0f,0.0f,0.0f);
			normal = glm::vec3(1.0f,0.0f,0.0f);
			color = glm::vec3(0.5f,0.5f,0.5f);
		}
		Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec3 col):position(pos), normal(norm), color(col)
		{}
	};

	std::vector<Model*>  decals;	
	std::vector<Vertex> vertexVector;
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	int edges;
	int sectors;

	glm::vec3 upVector;

};