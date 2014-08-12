#include "Avatar.h"
#include "CubeModel.h"

Avatar::Avatar(glm::vec3 position)
{
	head = new CubeModel(glm::vec3(0.1f,0.1f,0.1f));
	head->SetPosition(position);
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

	CubeModel* lLeg = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	lLeg->SetPosition(glm::vec3(-0.1f,-0.6f,0.0f));
	lLeg->SetParent(body);
	models.push_back(lLeg);

	CubeModel* rLeg = new CubeModel(glm::vec3(0.1f,0.5f,0.1f));
	rLeg->SetPosition(glm::vec3(0.1f,-0.6f,0.0f));
	rLeg->SetParent(body);
	models.push_back(rLeg);
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float dt)
{
	models[0]->SetPosition(mPosition);
	models[0]->SetRotation(mRotationAxis,mRotationAngleInDegrees);
	//mRotationAngleInDegrees += 90 * dt;
}

void Avatar::Draw()
{
	//draw all other parts of the plane
	for(int i = 0; i < models.size(); i++){
		models[i]->Draw();
	}
}