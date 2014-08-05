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
#include "BillboardModel.h"
#include "Text2DModel.h"

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	// Add a rectangular plane
  	BillboardModel* rM = new BillboardModel(glm::vec3(-10, 0, 0), glm::vec3(10, 0, 0), glm::vec3(0, 0, 1), 5.f, glm::vec3(0.1f, 0.5f, 0));
//  	RectangleModel* rM = new RectangleModel(glm::vec3(-10, 0, 0), glm::vec3(10, 0, 0), glm::vec3(0, 0, 1), 5.f, glm::vec3(0.1f, 0.5f, 0));	
  	world.addModel(rM);

	// Add our text.
	Text2DModel* tM = new Text2DModel("Hello, world!", 48, 100, 100);
	world.addModel(tM);

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
