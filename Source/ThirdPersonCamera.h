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
	virtual glm::vec3 performTransformation(glm::vec3 position,float angle, glm::vec3 axis);
private:
	Model* avatar;
	glm::vec3 mPosition;
	glm::vec3 direction;
	glm::vec3 mLookAt;
	glm::vec3 up;
	float horizontalAngle;
	float verticalAngle;
	float speed;
	float mouseSpeed;
	



};

