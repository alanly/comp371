//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera(glm::vec3 position);
	virtual ~FirstPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;



private:
	// @TODO 3 - Add every parameter you need for a first person camera
	//           including the speed of the camera

	glm::vec3 mPosition;	
	float horizontalAngle;
	// vertical angle : 0, look at the horizon
	float verticalAngle;
	// Initial Field of View
	float initialFoV;
 
	float speed; // 3 units / second
	float mouseSpeed;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;



};
