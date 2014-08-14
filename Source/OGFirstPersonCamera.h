//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"

class OGFirstPersonCamera : public Camera
{
public:
	OGFirstPersonCamera(glm::vec3 position);
	virtual ~OGFirstPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;

private:
	// @TODO 3 - Add every parameter you need for a first person camera
	//           including the speed of the camera

	glm::vec3 mPosition;  // Hold the camera position
	glm::vec3 mTarget;    // Hold the camera target
	glm::vec3 mUp;        // Hold the camera "up" vector
	glm::vec2 mAngle;     // Hold the camera angles for horizontal and vertical
	float     keySpeed;   // Specify the key input speed
	float     mouseSpeed; // Specify the mouse input speed
};
