//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "FirstPersonCameraT.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>


using namespace glm;

FirstPersonCameraT::FirstPersonCameraT(glm::vec3 position, Model* avatar): mPosition(position), avatar(avatar)
{
	distanceToTravel = 0;
	totalDistance = 0;
	increment = 1;
	// horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	verticalAngle = 0.0f;
 
	speed = 0.1f; // 3 units / second
	mouseSpeed = 0.1f;
	mPosition = position;

	std::vector<glm::vec3> points;
	points.push_back(glm::vec3(0.0f,0.0f,0.0f));
	points.push_back(glm::vec3(5.0f,5.0f,0.0f));
	points.push_back(glm::vec3(7.0f,5.0f,0.0f));
	points.push_back(glm::vec3(12.0f,3.0f,0.0f));
	points.push_back(glm::vec3(15.0f,5.0f,0.0f));
	points.push_back(glm::vec3(20.0f,0.0f,0.0f));
	FollowPath(points);
}

FirstPersonCameraT::~FirstPersonCameraT()
{
}

void FirstPersonCameraT::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();
	//displayVector(mPosition);
	if(followPath) {
			mPosition += direction * dt * speed;
			distanceToTravel = length(direction - mPosition);

			//std::cout << distanceToTravel << std::endl;
			if(distanceToTravel <= 0.2) {
				if(increment == path.size()-1) {
					followPath = false;
				}else {
					increment++;
					direction = path[increment] - mPosition;
					displayVector(direction);
					distanceToTravel = length(direction - mPosition);
				}
			}
	}else {
	
		// Get mouse position
		float xpos, ypos;
		xpos = -1 * EventManager::GetMouseMotionX();
		ypos = -1 * EventManager::GetMouseMotionY();

		horizontalAngle += mouseSpeed * dt * xpos;
		verticalAngle   += mouseSpeed * dt * ypos;

		direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

		right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
		);

		// Up vector : perpendicular to both direction and right
		up = glm::cross( right, direction );

		// Move forward
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W ) == GLFW_PRESS){
			mPosition += direction * dt * speed;
		}
		// Move backward
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S ) == GLFW_PRESS){
			mPosition -= direction * dt * speed;
		}
		// Strafe right
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D ) == GLFW_PRESS){
			mPosition += right * dt * speed;
		}
		// Strafe left
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A ) == GLFW_PRESS){
			mPosition -= right * dt * speed;
		}
	}
	
	avatar->SetPosition(mPosition);
}

glm::mat4 FirstPersonCameraT::GetViewMatrix() const
{
	glm::mat4 ViewMatrix = glm::lookAt(
							avatar->GetPosition(),           // Camera is here
							avatar->GetPosition()+direction, // and looks here : at the same position, plus "direction"
							up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	return ViewMatrix;
}
void FirstPersonCameraT::FollowPath(std::vector<glm::vec3> points) {
	path = points;
	followPath = true;
	mPosition = path[0];
	for(int i = 1; i < path.size()-1; i++) {
		totalDistance += length(path[i+1] - path[i]);
	}
	direction = path[increment] - path[increment-1];
	distanceToTravel = length(direction - mPosition);
}

void FirstPersonCameraT::displayVector(glm::vec3 v){ //DEBUG TOOL
	std::cout << "x: " << v.x << " y: " << v.y << " z: " << v.z <<std::endl;
}