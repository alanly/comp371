//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "World.h"
#include "Renderer.h"

#include "StaticCamera.h"
#include "FirstPersonCamera.h"

#include "CubeModel.h"
#include "ModelGroup.h"

#include "Light.h"

#include <GLFW/glfw3.h>
#include "EventManager.h"

using namespace std;
using namespace glm;

World::World()
{
	// Setup Camera
	mCamera.push_back( new StaticCamera( vec3(3.0f, 4.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) ) );
	mCamera.push_back( new FirstPersonCamera( vec3(0.5f, 0.5f, 5.0f) ) );
	mCurrentCamera = 0;
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		delete *it;
	}

	mModel.clear();

	// Camera
	for (vector<Camera*>::iterator it = mCamera.begin(); it < mCamera.end(); ++it)
	{
		delete *it;
	}
	mCamera.clear();

	// Light
	for (vector<Light*>::iterator it = mLight.begin(); it < mLight.end(); ++it)
	{
		delete *it;
	}
	mLight.clear();
}
	
void World::Update(float dt)
{
	// User Inputs
	// 0 1 2 to change the Camera
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1 ) == GLFW_PRESS)
	{
		mCurrentCamera = 0;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 1)
		{
			mCurrentCamera = 1;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 2)
		{
			mCurrentCamera = 2;
		}
	}

	// Spacebar to change the shader
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}
	
	// Update current Camera
	mCamera[mCurrentCamera]->Update(dt);

	// Update models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Update(dt);
	}
}

void World::addModel(Model* nModel)
{
	mModel.push_back(nModel);
}

void World::addLight(Light* nLight)
{
	mLight.push_back(nLight);
}

void World::Draw()
{
	Renderer::BeginFrame();

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Set our shader
		glUseProgram((*it)->GetShaderProgramID());

		// This looks for the MVP Uniform variable in the Vertex Program
		GLuint VPMatrixLocation = glGetUniformLocation((*it)->GetShaderProgramID(), "ViewProjectonTransform"); 

		// Send the view projection constants to the shader
		mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);
		
		// Draw model
		(*it)->Draw();
	}

	Renderer::EndFrame();
}
