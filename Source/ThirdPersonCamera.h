#pragma once
#include "camera.h"
#include "Model.h"


class ThirdPersonCamera :
	public Camera
{
public:
	ThirdPersonCamera(glm::vec3 position, Model* avatar);
	virtual ~ThirdPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;
	
	virtual void displayVector(glm::vec3 v);

private:
	Model* avatar;
	glm::vec3 mPosition;	
	glm::vec3 change;	
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;
	float speed; // 3 units / second
	float mouseSpeed;

	glm::vec3 mLookAt;
	glm::vec3 up;



};

