//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include "CubeModel.h"
#include <vector>

class ModelGroup : public Model
{
public:
	ModelGroup();
	virtual ~ModelGroup();

	virtual void Update(float dt);
	virtual void Draw();

	void addModel(Model* m,
				  glm::vec3 position,
				  glm::vec3 rotationAxis,
				  glm::vec3 scale,
				  float angle,
				  Model* parent);

private:
	// @TODO 5 - You may want a container for all the parts of your vehicle
	std::vector<Model*> container;

};
