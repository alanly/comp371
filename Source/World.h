//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//
//Written by Thomas Rahn, Tim Smith 
#pragma once

#include <vector>

class Camera;
class Model;

class World
{
public:
	World();
	~World();
	
	void Update(float dt);
	void Draw();

	void addModel(Model* nModel);

private:
	std::vector<Model*> mModel;

	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;
};
