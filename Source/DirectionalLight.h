/**
 * @author Alan Ly
 */

#pragma once
#include "light.h"


class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 position);
	~DirectionalLight(void);

	void SetLightPosition(float x, float y, float z);
};

