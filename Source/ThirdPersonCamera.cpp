#include "ThirdPersonCamera.h"

#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Avatar.h"

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* avatar): mPosition(position), avatar(avatar)
{
	// horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	verticalAngle = 0.0f;
 
	speed = 3.0f; // 3 units / second
	mouseSpeed = 1.0f;
	mPosition = position;
	mLookAt = glm::vec3(0,0,0);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}


ThirdPersonCamera::~ThirdPersonCamera(void)
{
}
void ThirdPersonCamera::Update(float dt){
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();
	
	// Get mouse position
	float xpos, ypos;
	xpos = -1 * EventManager::GetMouseMotionX();
	ypos = -1 * EventManager::GetMouseMotionY();

	float alpha = mouseSpeed * dt * ypos;
	float beta = mouseSpeed * dt * xpos;

	horizontalAngle += beta;
	verticalAngle   += alpha;

	glm::vec3 avatarPos = avatar->GetPosition();

	mPosition = performTransformation(mPosition, beta, glm::vec3(0,1,0));
	mPosition = performTransformation(mPosition, alpha, glm::vec3(1,0,0));
		

	avatar->SetRotation(glm::vec3(1,0,0), verticalAngle);
	avatar->SetRotation(glm::vec3(0,1,0), horizontalAngle);

	glm::vec3 forward = (avatar->GetPosition() - mPosition);
	glm::vec3 right = glm::vec3(glm::rotate(glm::mat4(1.0f),-90.0f,glm::vec3(0,1,0)) * glm::vec4(forward,0));
	
	// Move forward
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W ) == GLFW_PRESS){
		avatarPos += forward * dt * speed;
		mPosition += forward * dt * speed;
	}
	// Move backward
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S ) == GLFW_PRESS){
		avatarPos -= forward * dt * speed;
		mPosition -= forward * dt * speed;
	}
	// Strafe right
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D ) == GLFW_PRESS){
		avatarPos += right * dt * speed;
		mPosition += right * dt * speed;
	}
	// Strafe left
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A ) == GLFW_PRESS){
		avatarPos -= right * dt * speed;
		mPosition -= right * dt * speed;
	}
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS){
		avatarPos += glm::vec3(0,1,0) * dt * speed;
		mPosition += glm::vec3(0,1,0) * dt * speed;
	}
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		avatarPos -= glm::vec3(0,1,0) * dt * speed;
		mPosition -= glm::vec3(0,1,0) * dt * speed;
	}
	avatar->SetPosition(avatarPos);	
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	
	glm::mat4 ViewMatrix = glm::lookAt(
							mPosition,           // Camera is here
							avatar->GetPosition(), // and looks here : at the same position, plus "direction"
							glm::vec3(0,1,0)               // Head is up (set to 0,-1,0 to look upside-down)
						   );

	return ViewMatrix;
}


glm::vec3 ThirdPersonCamera::performTransformation(glm::vec3 position, float angle,  glm::vec3 axis)
{
	//glm::vec3 alignVector = glm::cross(glm::normalize(position), glm::normalize(axis));
	//float alignAngle = glm::acos(glm::dot(glm::normalize(axis),glm::normalize(position)));

	glm::mat4 translateToPoint = glm::translate(glm::mat4(1.0f), avatar->GetPosition());
	//glm::mat4 rotateToAlign = glm::rotate(glm::mat4(1.0f), alignAngle, alignVector);
	glm::mat4 rotateAroundAxis = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), -avatar->GetPosition());
	
	return  glm::vec3((translateToPoint  * rotateAroundAxis  * reverseTranslation) * glm::vec4(position,1));
}

void ThirdPersonCamera::displayVector(glm::vec3 v){ //DEBUG TOOL
	std::cout << "x: " << v.x << " y: " << v.y << " z: " << v.z <<std::endl;
}