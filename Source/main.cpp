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
#include <iostream>
#include <vector>
#include <map>

/*
static int createSphereBuffer(float radius, int latitudes, int longitudes) {

    int lst;

    lst = glGenLists(1);

    glNewList(lst, GL_COMPILE);
    {

        float latitude_increment = 360.0f / latitudes;
        float longitude_increment = 180.0f / longitudes;

        for (float u = 0; u < 360.0f; u += latitude_increment) {

            glBegin(GL_TRIANGLE_STRIP);

            for (float t = 0; t < 180.0f; t += longitude_increment) {

                float rad = radius;

                float x = (float) (rad * Math.sin(Math.toRadians(t)) * Math.sin(Math.toRadians(u)));
                float y = (float) (rad * Math.cos(Math.toRadians(t)));
                float z = (float) (rad * Math.sin(Math.toRadians(t)) * Math.cos(Math.toRadians(u)));

                vertex3f(x, y, z);

                float x1 = (float) (rad * Math.sin(Math.toRadians(t + longitude_increment)) * Math.sin(Math.toRadians(u + latitude_increment)));
                float y1 = (float) (rad * Math.cos(Math.toRadians(t + longitude_increment)));
                float z1 = (float) (rad * Math.sin(Math.toRadians(t + longitude_increment)) * Math.cos(Math.toRadians(u + latitude_increment)));

                vertex3f(x1, y1, z1);

            }

            glEnd();

        }

    }
    glEndList()

    return lst;

}

// to render VVVVVVVVV

// external variable in main file
static int sphereList = createSphereBuffer(desired parameters)

// called by the main program
void render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCallList(sphereList);

    // any additional rendering and buffer swapping if not handled already.

}*/

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;
	CubeModel* c = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	world.addModel(c);
	SphereModel* sphere = new SphereModel(3,4,4);
	sphere->Draw(1,1,1);
	
	//SphereModel* sphere = new SphereModel(3,4,4); 
	//world.addModel(IcoSphereCreator::Create(5));

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
