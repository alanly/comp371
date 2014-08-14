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
#include "PointLight.h"


int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	// Create and add our lighting to the world
	PointLight* light1 = new PointLight(glm::vec3(5.f, 0.f, 0.f));
	world.addLight(light1);

	PointLight* light2 = new PointLight(glm::vec3(5.f, -10.f, 0.f));
	world.addLight(light2);

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
