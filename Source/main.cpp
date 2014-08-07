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
#include "RectangleModel.h"
#include "ArcModel.h"
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
	path.push_back(glm::vec3(12.0f,3.0f,2.0f));
	path.push_back(glm::vec3(15.0f,3.0f,2.0f));
	path.push_back(glm::vec3(20.0f,1.0f,0.0f));
	path.push_back(glm::vec3(24.0f,1.0f,2.0f));
	path.push_back(glm::vec3(28.0f,1.0f,0.0f));
	path.push_back(glm::vec3(30.0f, 2.0f, 0.0f));
	path.push_back(glm::vec3(35.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(36.0f, 3.0f, -1.0f));
	path.push_back(glm::vec3(37.0f, 3.0f, -2.0f));
	path.push_back(glm::vec3(38.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(39.0f, 3.0f, 1.0f));
	path.push_back(glm::vec3(43.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(50.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(60.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(61.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(62.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(63.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(64.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(65.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(66.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(67.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(68.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(69.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(75.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(76.0f, 3.0f, 0.0f));

	

	Portal* p = new Portal(path, 1.0f, 8);

	CubeModel* c = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	c->SetPosition(glm::vec3(-1.0f, -1.0f, -1.0f));

	RectangleModel* rm = new RectangleModel(glm::vec3(0.0f,0.0f,0.0f),
											glm::vec3(1.0f,1.0f,1.0f), 
											glm::vec3(1.0f,0.0f,0.0f),
											2.0f, glm::vec3(1.0f,0.0f,0.0f));
	
	//world.addModel(c);
	//world.addModel(rm);
	/*
	ArcModel* am = new ArcModel(glm::vec4(1.0f, 0.0f, 0.0f,0.5f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		1.5f,
		2.0f,
		90.0f,
		20);

	ArcModel* am2 = new ArcModel(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 1.0f , 0.0f),
		glm::vec3(5.0f, 0.0f, 0.0f),
		0.0f,
		2.0f,
		360.0f,
		30);

	ArcModel* am3 = new ArcModel(glm::vec4(-3.0f, 0.0f, 0.0f, 0.8f),
		glm::vec4(0.0f, 1.0f, 0.0f,0.8f),
		glm::vec3(-5.0f, 0.0f, 0.0f),
		1.0f,
		2.0f,
		270.0f,
		20);`
		world.addModel(am);
	world.addModel(am2);
	world.addModel(am3);*/
	world.addModel(p);// portal!
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
