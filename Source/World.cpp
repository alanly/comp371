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
#include "FirstPersonCameraT.h"

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
	CubeModel * myc = new CubeModel(vec3(1.0f, 1.0f, 1.0f));
	addModel(myc);
	FirstPersonCameraT * myt = new FirstPersonCameraT(vec3(0.5f, 0.5f, 5.0f),myc);
	

	//Camera * myCam = mCamera[2];


	std::vector<glm::vec3> path;

	path.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	path.push_back(glm::vec3(5.0f, 2.0f, 0.0f));
	path.push_back(glm::vec3(7.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(12.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(15.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(20.0f, 1.0f, 0.0f));
	path.push_back(glm::vec3(24.0f, 1.0f, 0.0f));
	path.push_back(glm::vec3(28.0f, 1.0f, 0.0f));
	path.push_back(glm::vec3(30.0f, 2.0f, 0.0f));
	path.push_back(glm::vec3(35.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(36.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(37.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(38.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(39.0f, 3.0f, 0.0f));
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


	myt->FollowPath(path);

	mCamera.push_back(myt);
	mCurrentCamera = 2;
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
	
	// Set Shader... In a more sofisticated application, each model could use a different shader
	// In our case, all the models use a common shader
	glUseProgram(Renderer::GetShaderProgramID());

	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectonTransform"); 

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Send the view projection constants to the shader
		mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);
		
		// Draw model
		(*it)->Draw();
	}

	Renderer::EndFrame();
}
