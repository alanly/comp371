//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "ModelGroup.h"
#include "CubeModel.h"


using namespace std;
using namespace glm;

void ModelGroup::addModel(Model* m,
						  glm::vec3 position,
						  glm::vec3 rotationAxis,
						  glm::vec3 scale,
						  float angle,
						  Model* parent)
{
	m->SetPosition(position);
	m->SetRotation(rotationAxis, angle);
	m->SetScaling(scale);
	m->SetParent(parent);

	container.push_back(m);
}

ModelGroup::ModelGroup()
{
}

ModelGroup::~ModelGroup()
{
}

void ModelGroup::Update(float dt)
{	
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
}

void ModelGroup::Draw()
{
	container[0]->SetPosition(mPosition);
	container[0]->SetRotation(mRotationAxis,mRotationAngleInDegrees);
	container[0]->SetScaling(mScaling);

	for(unsigned int i=0;i<container.size();i++){
		container[i]->Draw();
	}
	// @TODO 5 - Draw Each part of your vehicle here
}