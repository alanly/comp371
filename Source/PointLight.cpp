/**
 * @author Alan Ly
 */

#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::PointLight(glm::vec3 position)
{
	SetLightPosition(
		position.x,
		position.y,
		position.z
		);
}


PointLight::~PointLight(void)
{
}


void PointLight::SetLightPosition(float x, float y, float z)
{
	lPosition.x = x;
	lPosition.y = y;
	lPosition.z = z;
	lPosition.w = 1.f;
}