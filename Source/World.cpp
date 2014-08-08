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

void World::addModel(Model* nModel){
	mModel.push_back(nModel);
}

void World::Draw()
{
	Renderer::BeginFrame();

	// Get the current camera
	Camera* CurrentCamera = mCamera[mCurrentCamera];

	// Get the View Projection matrix
	mat4 VP = CurrentCamera->GetViewProjectionMatrix();

	// Get the View matrix
	mat4 ViewMatrix = CurrentCamera->GetViewMatrix();

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Get the model's shader program
		unsigned int ShaderProgramID = (*it)->GetShaderProgramID();

		// Set our shader
		glUseProgram(ShaderProgramID);

		// This looks for the MVP Uniform variable in the Vertex Program
		GLuint VPMatrixLocation = glGetUniformLocation(ShaderProgramID, "ViewProjectonTransform");

		// Send the view projection constants to the shader
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

		GLuint CameraRight_worldspace_ID = glGetUniformLocation(ShaderProgramID, "CameraRight_worldspace");
		GLuint CameraUp_worldspace_ID = glGetUniformLocation(ShaderProgramID, "CameraUp_worldspace");
		
		glUniform3f(CameraRight_worldspace_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		glUniform3f(CameraUp_worldspace_ID, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
		
		// Draw model
		(*it)->Draw();
	}

	Renderer::EndFrame();
}
