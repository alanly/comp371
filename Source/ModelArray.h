//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include <vector>

class ModelArray : public Model
{
public:
	ModelArray();
	virtual ~ModelArray();

	virtual void Update(float dt);
	virtual void Draw();

	void addModel(std::vector<Model*> m,
			glm::vec3 offset);

private:
	// @TODO 5 - You may want a container for all the parts of your vehicle
	std::vector<Model*> container;

};
