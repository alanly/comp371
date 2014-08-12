//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

/**
 * @author Alan Ly (per-model shaders, material coefficients)
 */

#include "Model.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;

Model::Model(Model* m, unsigned int shaderProgramID) : 
	mName("UNNAMED"),
	mPosition(0.0f,0.0f,0.0f),
	mScaling(1.0f,1.0f,1.0f),
	mRotationAxis(0.0f,1.0f,0.0f),
	mRotationAngleInDegrees(0.0f),
	mParent(m),
	mMaterialCoefficients(0.2f,0.8f,0.2f,50.f)
{
	mShaderProgramID = (shaderProgramID == 0) ? Renderer::GetShaderProgramID() : shaderProgramID;
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

	if (mParent!=NULL) 
	{
		worldMatrix = glm::translate(worldMatrix, mPosition+(mParent->mPosition));
		worldMatrix = glm::rotate(worldMatrix,mRotationAngleInDegrees+(mParent->mRotationAngleInDegrees), mRotationAxis+(mParent->mRotationAxis));
		worldMatrix = glm::scale(worldMatrix, mScaling*(mParent->mScaling));
	}
	else
	{
		worldMatrix = glm::translate(worldMatrix, mPosition);
		worldMatrix = glm::rotate(worldMatrix,mRotationAngleInDegrees, mRotationAxis);
		worldMatrix = glm::scale(worldMatrix, mScaling);
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

void Model::SetMaterialCoefficients(glm::vec4 coefficients)
{
	mMaterialCoefficients = coefficients;
}