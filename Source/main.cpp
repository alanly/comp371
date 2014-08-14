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
#include "SphereModel.h"
#include "PlaneModel.h"
#include "SOIL.h"
#include "UTFConvert.h"
#include "LSystemModel.h"
#include "RectangleModel.h"
#include "ArcModel.h"
#include "Portal.h"
#include "Text2DModel.h"
#include "SpiralModel.h"

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;
    std::string lsys  = getLSystemString();
    //LSystemModel lsModel = new LSystemModel(lsys);


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


	SpiralModel* spiral = new SpiralModel(glm::vec4(1.0f,0.0f,0.0f,1.0f) , //color
		     glm::vec4(0.0f,0.0f,1.0f,1.0f), //color2
			 glm::vec3(0.0f,0.0f,0.0f), //Position
			 glm::vec3(1.0f,0.0f,0.0f), //Normal (up vector)
			 glm::vec3(0.0f,0.0f,1.0f), //Binormal
			 2.0f, //Radius 1
			 4.0f, //Radius 2
			 360.0f * 7.5f, //Arc Angle
			 500,		//arbitrary # edges
			 15.0f);	//arbitrary height

	//world.addModel(p);// portal!
	//world.addModel(c);

	world.addModel(spiral);
	
	PlaneModel* pPlaneModel = new PlaneModel(glm::vec3(1.0f,1.0f,1.0f));
	world.addModel(pPlaneModel);


   //====== Load texture
    GLuint tex;
    glGenTextures(1, &tex);

    int width, height;
    unsigned char* image = SOIL_load_image(UTFConvert::GetImagePath("Scottish_Fold.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    glDeleteTextures(1, &tex); //remove texture from openGL
	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
