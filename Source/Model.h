//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

/**
 * @author Alan Ly (per-model shaders, material coefficients)
 * @author Tim Smith (collisions)
 */

#pragma once


#include <vector>

#include <GLM/glm.hpp>
#include <GL\glew.h>

#include "Camera.h"


class Model
{
public:
	
	Model(Model* m = NULL, unsigned int shaderProgramID = 0);
	virtual ~Model();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	virtual glm::mat4 GetWorldMatrix() const;

	void SetYAxis(glm::vec3 yAxis);
	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);
	void SetParent(Model* par);
	void SetMaterialCoefficients(glm::vec4 coefficients);
	void SetShader(unsigned int shaderID);

	glm::vec3    GetPosition()        const	{ return mPosition; }
	glm::vec3    GetScaling()         const	{ return mScaling; }
	glm::vec3    GetRotationAxis()    const	{ return mRotationAxis; }
	float        GetRotationAngle()   const	{ return mRotationAngleInDegrees; }
	unsigned int GetShaderProgramID() const { return mShaderProgramID; }
	
	//collisions
	bool collides(Model* other);
	void setCollisionBoxSize(glm::vec3 dimensions);//absolute width/height/depth of the box!

	Model* rotaterX;
	Model* rotaterY;
	// Expressed as (ka, kd, ks, n)
	glm::vec4 GetMaterialCoefficients() const { return mMaterialCoefficients; }

	void PrepareDraw(Camera* currentCamera, unsigned int numOfLights, GLfloat* lightPositions, GLfloat* lightColors, GLfloat* lightCoefficients);

protected:

	float        mRotationAngleInDegrees;
	glm::vec3    mPosition;
	glm::vec3    mScaling;
	glm::vec3    mRotationAxis;
	glm::vec4    mMaterialCoefficients;
	glm::vec3    mCollisionBoxSize;
	Model*	     mParent;
	std::string  mName;
	unsigned int mShaderProgramID;
};
