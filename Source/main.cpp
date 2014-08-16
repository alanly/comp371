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
#include "PointLight.h"
#include "Text2DModel.h"
#include "SpiralModel.h"

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;
    std::string lsys  = getLSystemString();
    //LSystemModel lsModel = new LSystemModel(lsys);
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
			 
	world.addModel(spiral);
	
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

    glDeleteTextures(1, &tex); //remove texture from openGL
	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
