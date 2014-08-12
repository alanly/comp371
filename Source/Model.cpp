//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;

Model::Model() : mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f), mRotationAngleInDegrees(0.0f),mParent(NULL),mYAxis(0,0,0)
{
}

Model::Model( Model &m) : mName("UNNAMED"), mPosition(0.0f,0.0f,0.0f), mScaling(1.0f,1.0f,1.0f),mRotationAxis(0.0f,1.0f,0.0f),mRotationAngleInDegrees(0.0f),mParent( &m),mYAxis(0,0,0)
{
}

Model::~Model()
{
}

void Model::Update(float dt)
{
}

void Model::Draw()
{
}

glm::mat4 Model::GetWorldMatrix() const
{
	glm::mat4 worldMatrix(1.0f);
	worldMatrix = glm::translate(worldMatrix, mPosition);
	worldMatrix = glm::rotate(worldMatrix,mRotationAngleInDegrees, mRotationAxis);
	worldMatrix = glm::scale(worldMatrix, mScaling);

	if(mParent!=NULL){
		worldMatrix = mParent->GetWorldMatrix()*worldMatrix;
	}

	return worldMatrix;
}

void Model::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void Model::SetParent(Model* par)
{
	mParent = par;
}

void Model::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void Model::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}
void Model::SetYAxis(glm::vec3 yAxis)
{
	mYAxis = yAxis;

}