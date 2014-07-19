//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "FirstPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>



using namespace glm;

FirstPersonCamera::FirstPersonCamera(glm::vec3 position) : Camera()
{
	// horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	verticalAngle = 0.0f;
	// Initial Field of View
	initialFoV = 45.0f;
 
	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.1f;
	mPosition = position;
	glm::vec3 direction();
	glm::vec3 right();
	glm::vec3 up();
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();


	// @TODO 3 : You need to move the Camera based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion



	//////////////////////////////////////////////////////////////
	
	// Get mouse position
	int xpos, ypos;
	xpos = -1 * EventManager::GetMouseMotionX();
	ypos = -1 * EventManager::GetMouseMotionY();

	horizontalAngle += mouseSpeed * dt * float( xpos );
	verticalAngle   += mouseSpeed * dt * float( ypos );

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

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	// @TODO 3 : Calculate the View Matrix
	//glm::mat4 viewMatrix(1.0f);
	
	glm::mat4 ViewMatrix = glm::lookAt(
							mPosition,           // Camera is here
							mPosition+direction, // and looks here : at the same position, plus "direction"
							up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	return ViewMatrix;
}
