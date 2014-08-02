//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Renderer.h"
#include "Generator.h"
#include "World.h"
#include "EventManager.h"
#include "CubeModel.h"
#include "LSystemModel.h"
#include "Text2DModel.h"

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

    std::string lsys  = getLSystemString();
    LSystemModel lsModel = new LSystemModel(lsys);

    //world.addModel(lsysmodel);

	// Add a cube model
	CubeModel* cM = new CubeModel();
	cM->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	cM->SetScaling(glm::vec3(10.0f, 10.0f, 0.01f));
	world.addModel(cM);

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
