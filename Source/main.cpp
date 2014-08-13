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


int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;
	//CubeModel* c = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	//world.addModel(c);
	SphereModel* sphere = new SphereModel(glm::vec3(0.f,0.f,0.f), 1.0f, 8, 8, glm::vec4(1.f,0.f,0.f,1.f));
	world.addModel(sphere);
	//SphereModel* sphere2 = new SphereModel(glm::vec3 (5.f, 0.f, 0.f), 3.f, 30, 16, glm::vec4(1.f, 0.f, 0.f, 1.f));
	//world.addModel(sphere2);
	



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
