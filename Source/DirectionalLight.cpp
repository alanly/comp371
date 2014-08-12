/**
 * @author Alan Ly
 */

#include "DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
}


DirectionalLight::DirectionalLight(glm::vec3 position)
{
	SetLightPosition(
		position.x,
		position.y,
		position.z
		);
}


DirectionalLight::~DirectionalLight(void)
{
}


void DirectionalLight::SetLightPosition(float x, float y, float z)
{
	lPosition.x = x;
	lPosition.y = y;
	lPosition.z = z;
	lPosition.w = 0.f;
}