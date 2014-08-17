#pragma once
#include "model.h"
#include <GLM/glm.hpp>
#include <vector>

class PortalEntrance :
	public Model
{
public:
	PortalEntrance(glm::vec3 Position,glm::vec3 Normal, glm::vec3 Binormal,int numParts);
	~PortalEntrance(void);

	void Update(float dt);
	void Draw();
private:
	std::vector<Model*> collection;
		glm::vec3 mNormal;
		glm::vec3 mBiNormal;
};

