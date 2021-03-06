//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"
#include "Model.h"
#include "vector"

class FirstPersonCameraT : public Camera
{
public:
	FirstPersonCameraT(glm::vec3 position, Model* avatar);
	virtual ~FirstPersonCameraT();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;
	virtual void FollowPath(std::vector<glm::vec3> points);

	virtual void displayVector(glm::vec3 v);
private:
	bool followPath;
	Model* avatar;
	glm::vec3 mPosition;	
	float horizontalAngle;
	// vertical angle : 0, look at the horizon
	float verticalAngle;
	float distanceToTravel;
	float totalDistance;
	int increment;
	float speed; 
	float mouseSpeed;
	std::vector<glm::vec3> path;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
	glm::bvec3 lt;


};
/*
for(int i = 0; i<number of points -1; i++)
	distanceToTravel = length(vec[i]-vec[i+1]
	distanceForThisIT = normalize(distanceToTravel)*speed

	for(int j = 0; j<distanceToTravel; j+distanceForThisIT)
		camera.position+=distanceForThisIT;

		if( more than turnRange through this vector
			OR
		    less than turnRange through this vector) //first segment or last segment of a path
			increment angle()
			*/