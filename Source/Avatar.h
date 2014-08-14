//Written by Thomas Rahn

#pragma once
#include "model.h"
#include <vector>

class Avatar : public Model
{

public:
	Avatar(glm::vec3 position);
	~Avatar(void);
	virtual void Update(float dt);
	virtual void Draw();
private:
	float leftAngle;
	float rightAngle;
	int flipper;
	std::vector<Model*> models; 
	Model* head;
	Model* rLeg;
	Model* lLeg;
};

