//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Camera.h"
#include <GLM/gtx/transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	// @TODO 1 - Calculate View Projection Matrix


// (1.0f,); // identity, you need to change this

	return GetProjectionMatrix()*GetViewMatrix();
	//return viewProjection;
}

glm::mat4 Camera::GetViewMatrix() const{
	return	glm::lookAt(
					 glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
					 glm::vec3(0,0,0), // and looks at the origin
					 glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
				     );
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}
