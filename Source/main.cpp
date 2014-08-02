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
#include "PlaneModel.h"
#include "SOIL.h"
#include "UTFConvert.h"


int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;
	PlaneModel* p = new PlaneModel(glm::vec3(1.0f,1.0f,1.0f));
	world.addModel(p);

    // Load texture
    GLuint tex;
    glGenTextures(1, &tex);

    int width, height;
    unsigned char* image = SOIL_load_image("C:\\Users\\Tiffany\\Google Drive\\COMP371\\Project\\Source\\Images\\alphalogo_a4arial.png", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
