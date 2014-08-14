//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "OGFirstPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>



using namespace glm;

OGFirstPersonCamera::OGFirstPersonCamera(glm::vec3 position) : Camera()
{
	mPosition  = position;
	mTarget    = glm::vec3(0.0f, 0.0f, 0.0f);
	mUp        = glm::vec3(0.0f, 1.0f, 0.0f);
	mAngle     = glm::vec2(3.14f, 0.0f);
	keySpeed   = 1.5;
	mouseSpeed = -0.5f;
}

OGFirstPersonCamera::~OGFirstPersonCamera()
{
}

void OGFirstPersonCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();


	// @TODO 3 : You need to move the Camera based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion

	// Handle Mouse Input

	// Calculate our camera target angles
	mAngle.x += mouseSpeed * dt * EventManager::GetMouseMotionX();
	mAngle.y += mouseSpeed * dt * EventManager::GetMouseMotionY();
	// Generate our targeting vector
	mTarget = glm::vec3(
		glm::cos(mAngle.y) * glm::sin(mAngle.x),
		glm::sin(mAngle.y),
		glm::cos(mAngle.y) * glm::cos(mAngle.x)
	);
	// Generate our "right" vector
	glm::vec3 right = glm::vec3(
		glm::sin(mAngle.x - (3.14f/2.0f)),
		0,
		glm::cos(mAngle.x - (3.14f/2.0f))
	);
	// Calculate our camera "up" vector
	mUp = glm::cross(right, mTarget);
	
	// Handle Key Input
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition += mTarget * dt * keySpeed;
	}

	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition -= right * dt * keySpeed;
	}

	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		mPosition -= mTarget * dt * keySpeed;
	}

	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition += right * dt * keySpeed;
	}

	// Handle speed sensitivity adjustment
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_PAGE_UP) == GLFW_PRESS)
	{
		keySpeed += 2 * dt;
		mouseSpeed -= 0.75 * dt;

		printf("(keySpeed, mouseSpeed) = (%f, %f)\n", keySpeed, mouseSpeed);
	}

	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
	{
		keySpeed -= 2 * dt;
		mouseSpeed += 0.75 * dt;

		printf("(keySpeed, mouseSpeed) = (%f, %f)\n", keySpeed, mouseSpeed);
	}
}

glm::mat4 OGFirstPersonCamera::GetViewMatrix() const
{
	// @TODO 3 : Calculate the View Matrix
	glm::mat4 viewMatrix = glm::lookAt(mPosition, mPosition+mTarget, mUp);
	
	return viewMatrix;
}