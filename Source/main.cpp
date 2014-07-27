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
	CubeModel* c = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	world.addModel(c);
	//SphereModel* sphere = new SphereModel(3,4,4); 
	//world.addModel(sphere);

	//GLfloat lightpos[] = {10, 10, 10, 1.0}; 
//	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	//glli

	GLuint programID = Renderer::LoadShaders( "../Source/Shaders/StandardShading.vertexshader", "../Source/Shaders/StandardShading.fragmentshader" );


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
