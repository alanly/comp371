//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Renderer.h"
#include "World.h"
#include "EventManager.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "Portal.h"


int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	std::vector<glm::vec3> path;

	path.push_back(glm::vec3(0.0f,0.0f,0.0f));
	path.push_back(glm::vec3(5.0f,2.0f,0.0f));
	path.push_back(glm::vec3(7.0f,3.0f,0.0f));
	path.push_back(glm::vec3(12.0f,4.0f,0.0f));
	path.push_back(glm::vec3(15.0f,3.0f,0.0f));
	path.push_back(glm::vec3(20.0f,1.0f,0.0f));
	path.push_back(glm::vec3(24.0f,3.0f,0.0f));
	path.push_back(glm::vec3(28.0f,1.0f,0.0f));
	path.push_back(glm::vec3(30.0f,2.0f,0.0f));
	path.push_back(glm::vec3(35.0f,3.0f,0.0f));


	Portal* p = new Portal(path, 1.0f, 24);

	CubeModel* c = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	world.addModel(p);
	//world.addModel(c);
	

	// Main Loop
	do
	{
		// Update Event Manager - Frame time / input / events processing 
		EventManager::Update();

		// Update World
		float dt = EventManager::GetFrameTime();
		world.Update(dt);

		// Draw World
		world.Draw();

	}
	while(EventManager::ExitRequested() == false);

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
