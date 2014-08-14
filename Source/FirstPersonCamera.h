//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//
//Written by Thomas Rahn
#pragma once

#include "Camera.h"
#include "Model.h"
#include "vector"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera(glm::vec3 position, Model* avatar);
	virtual ~FirstPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;
	void FollowPath(std::vector<glm::vec3> points);

	virtual void displayVector(glm::vec3 v);
private:
	bool followPath;
	Model* avatar;
	glm::vec3 mPosition;	
	float horizontalAngle;
	float verticalAngle;
	float distanceToTravel;
	float totalDistance;
	int increment;
	float speed; 
	float mouseSpeed;
	std::vector<glm::vec3> path;
	glm::vec3 direction;
	glm::vec3 look;
	glm::vec3 right;
	glm::vec3 up;
	float prevDistance;


};