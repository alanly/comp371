//Written by Thomas Rahn

#include "FirstPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/common.hpp>
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

#include <windows.h>

using namespace glm;

FirstPersonCamera::FirstPersonCamera(glm::vec3 position, Model* avatar): mPosition(position), avatar(avatar)
{
	distanceToTravel = 0;
	totalDistance = 0;
	increment = 1;
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	followPath = false;
	speed = 3.5f; // 3 units / second
	mouseSpeed = 0.05f;
	mPosition = position;
	prevDistance = -1;
	look = mPosition;
	direction = glm::vec3(0,0,0);
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();

	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_T ) == GLFW_PRESS){
		speed += 1;
	}
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_Y ) == GLFW_PRESS){
		if(speed > 1)
			speed -= 1;
	}

	if(followPath) {
		mPosition += (direction-mPosition) * dt * speed;
		distanceToTravel = length(path[increment] - mPosition);

		if(distanceToTravel < 3.0f && increment < path.size()-1) {
			float percentage = 1-(distanceToTravel/3.0f);
			float x = path[increment].x + ((path[increment+1].x - path[increment].x) * percentage);
			float y = path[increment].y + ((path[increment+1].y - path[increment].y) * percentage);
			float z = path[increment].z + ((path[increment+1].z - path[increment].z) * percentage);
			direction = glm::vec3(x,y,z);
		}
		if(prevDistance < distanceToTravel || distanceToTravel < 0.1f) {
			if(increment == path.size()-1) {
				followPath = false;
				increment = 0;
				avatar->SetRotation(glm::vec3(0,1,0),90.f);
				horizontalAngle = 1.5f;
				verticalAngle = 0.5f;
				path.clear();
			}else {
				increment++;
				direction = path[increment];
				distanceToTravel = length(direction - mPosition);
			}
		}

		glm::vec3 lookAtVector = direction - mPosition;

		right = glm::vec3(glm::rotate(glm::mat4(1.0f),90.0f, glm::vec3(0,1,0)) * glm::vec4(lookAtVector,1));
		up = normalize(glm::cross(lookAtVector,right));

		prevDistance = distanceToTravel;
	}else {
		// Get mouse position
		float xpos, ypos;
		xpos = -1 * EventManager::GetMouseMotionX();
		ypos = -1 * EventManager::GetMouseMotionY();

		float beta = mouseSpeed * dt * xpos;
		float alpha = mouseSpeed * dt * ypos;

		horizontalAngle += beta;
		verticalAngle   += alpha;
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
		avatar->SetPosition(performTransformation(avatar->GetPosition(), beta, glm::vec3(0,1,0)));
		avatar->SetPosition(performTransformation(avatar->GetPosition(), alpha, glm::vec3(1,0,0)));
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
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS){
			mPosition += glm::vec3(0,1,0) * dt * speed;
		}
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		
			mPosition -= glm::vec3(0,1,0) * dt * speed;
		}
	}
	look = mPosition + direction;
	displayVector(mPosition);
	avatar->SetPosition(mPosition);
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	glm::mat4 ViewMatrix = glm::lookAt(
							avatar->GetPosition(),           // Camera is here
							look, // and looks here : at the same position, plus "direction"
							up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	return ViewMatrix;
}

void FirstPersonCamera::FollowPath(std::vector<glm::vec3> points) {
	path = points;
	up = glm::vec3(0,1,0); //inital up vector
	followPath = true;
	mPosition = path[0]; // set position to the first point of the tube
	direction = path[increment];
	distanceToTravel = length(direction - mPosition);
	prevDistance = distanceToTravel;
}

glm::vec3 FirstPersonCamera::performTransformation(glm::vec3 position, float angle,  glm::vec3 axis)
{
	glm::mat4 translateToPoint = glm::translate(glm::mat4(1.0f), avatar->GetPosition());
	glm::mat4 rotateAroundAxis = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), -avatar->GetPosition());
	
	return  glm::vec3((translateToPoint  * rotateAroundAxis  * reverseTranslation) * glm::vec4(position,1));
}

void FirstPersonCamera::displayVector(glm::vec3 v){ //DEBUG TOOL
	std::cout << "x: " << v.x << " y: " << v.y << " z: " << v.z <<std::endl;
}