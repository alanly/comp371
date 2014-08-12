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

#pragma once


#include <vector>

#include <GLM/glm.hpp>


class Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	Model(Model* m = NULL, unsigned int shaderProgramID = 0);
	virtual ~Model();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;


	virtual glm::mat4 GetWorldMatrix() const;

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);
	void SetParent(Model* par);
	void SetMaterialCoefficients(glm::vec4 coefficients);

	glm::vec3    GetPosition()        const	{ return mPosition; }
	glm::vec3    GetScaling()         const	{ return mScaling; }
	glm::vec3    GetRotationAxis()    const	{ return mRotationAxis; }
	float        GetRotationAngle()   const	{ return mRotationAngleInDegrees; }
	unsigned int GetShaderProgramID() const { return mShaderProgramID; }

	// Expressed as (ka, kd, ks, n)
	glm::vec4    GetMaterialCoefficients() const { return mMaterialCoefficients; }

protected:
	std::string mName;
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

	// @TODO 4 - You may want to add a parent object for the hierarchical modeling

	Model*	  mParent;

	unsigned int mShaderProgramID;

	glm::vec4 mMaterialCoefficients;
};
