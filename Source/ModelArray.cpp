
// Author: Tim Smith

#include "ModelArray.h"


using namespace std;
using namespace glm;

void ModelArray::addModel(vector<Model*> m,
						glm::vec3 offset)
{
	int count = m.size();

	for (int i = 0; i < count; i++)
	{
		m[i]->SetPosition(m[i]->GetPosition() + offset*(float)i);
		container.push_back(m[i]);
	}

	//container.push_back(m);
}

ModelArray::ModelArray()
{
}

ModelArray::~ModelArray()
{
}

void ModelArray::Update(float dt)
{
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
}

void ModelArray::Draw()
{
	container[0]->SetPosition(mPosition);
	container[0]->SetRotation(mRotationAxis, mRotationAngleInDegrees);
	container[0]->SetScaling(mScaling);

	for (unsigned int i = 0; i < container.size(); i++){
		container[i]->Draw();
	}
	// @TODO 5 - Draw Each part of your vehicle here
}