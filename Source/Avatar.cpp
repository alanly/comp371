//Written by Thomas Rahn

#include "Avatar.h"
#include "CubeModel.h"
#include <iostream>
Avatar::Avatar(glm::vec3 position)
{
	leftAngle = 0.0f;
	rightAngle = 0.0f;
	rotaterX= new CubeModel(glm::vec3(0,0,0));
	rotaterX->SetPosition(position);
	models.push_back(rotaterX);

	rotaterY = new CubeModel(glm::vec3(0,0,0));
	rotaterY->SetPosition(glm::vec3(0,0,0));
	rotaterY->SetParent(rotaterX);
	models.push_back(rotaterY);


	head = new CubeModel(glm::vec3(0.1f,0.1f,0.1f));
	head->SetPosition(glm::vec3(0,0,0));
	models.push_back(head);

	CubeModel* body = new CubeModel(glm::vec3(0.5f,0.5f,0.1f));
	body->SetPosition(glm::vec3(0.0f,-0.3f,0.0f));
	body->SetParent(head);
	models.push_back(body);


	CubeModel* lArm = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	lArm->SetPosition(glm::vec3(-0.35f,-0.1f,0.0f));
	lArm->SetParent(body);
	models.push_back(lArm);
	

	CubeModel* rArm = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	rArm->SetPosition(glm::vec3(0.35f,-0.1f,0.0f));
	rArm->SetParent(body);
	models.push_back(rArm);

	lLeg = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	lLeg->SetPosition(glm::vec3(-0.1f,-0.5f,0.0f));
	
	lLeg->SetParent(body);

	models.push_back(lLeg);

	rLeg = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	rLeg->SetPosition(glm::vec3(0.1f,-0.5f,0.0f));
	
	rLeg->SetParent(body);
	models.push_back(rLeg);

	flipper = 1;
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float dt)
{
	head->SetPosition(mPosition);
	head->SetRotation(mRotationAxis,mRotationAngleInDegrees);

	/*
	leftAngle += (45.0f * dt * flipper);
	rightAngle += (45.0f * dt * -flipper);

	std::cout << "left: " << leftAngle << " right: " << rightAngle << std::endl;

	if(leftAngle > 45.0f || rightAngle > 45.0f){
		flipper = flipper * -1;
	}

	rLeg->SetRotation(glm::vec3(1,0,0),rightAngle);
	lLeg->SetRotation(glm::vec3(1,0,0),leftAngle);
	*/
}

void Avatar::Draw()
{
	//draw all other parts of the plane
	for(int i = 0; i < models.size(); i++){
		models[i]->Draw();
	}
}