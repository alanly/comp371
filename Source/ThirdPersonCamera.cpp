#include "ThirdPersonCamera.h"

#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* avatar): mPosition(position), avatar(avatar)
{
	// horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	verticalAngle = 0.0f;
 
	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.1f;
	mPosition = position;
	mLookAt = glm::vec3(0,0,0);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	// Initial Field of View
	initialFoV = 45.0f;
	change = glm::vec3(0,0,0);
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

	horizontalAngle += mouseSpeed * dt * xpos;
	verticalAngle   += mouseSpeed * dt * ypos;

	std::cout << "H: " << horizontalAngle << " V:" << verticalAngle << std::endl;

	glm::vec3 direction = glm::vec3(
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector : perpendicular to both direction and right
	up = glm::cross( right, direction );
	glm::vec3 avatarPos = avatar->GetPosition();

	// Move forward
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W ) == GLFW_PRESS){
		avatarPos += direction * dt * speed;
		change += direction * dt * speed;
	}
	// Move backward
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S ) == GLFW_PRESS){
		avatarPos -= direction * dt * speed;
		change -= direction * dt * speed;
	}
	// Strafe right
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D ) == GLFW_PRESS){
		avatarPos += right * dt * speed;
		change += right * dt * speed;
	}
	// Strafe left
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A ) == GLFW_PRESS){
		avatarPos -= right * dt * speed;
		change -= right * dt * speed;
	}
	avatar->SetPosition(avatarPos);

	
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	
	glm::mat4 ViewMatrix = glm::lookAt(
							mPosition + change,           // Camera is here
							avatar->GetPosition(), // and looks here : at the same position, plus "direction"
							up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	return ViewMatrix;
}