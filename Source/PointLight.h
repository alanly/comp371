/**
 * @author Alan Ly
 */

#pragma once
#include "light.h"


class PointLight : public Light
{
public:
	PointLight();
	PointLight(glm::vec3 position);
	~PointLight(void);

	void SetLightPosition(float x, float y, float z);
};

