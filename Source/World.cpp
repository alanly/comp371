//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

/**
 * @author Alan Ly (multiple scene-lighting, per-model shaders)
 */

//Written by Thomas Rahn, Tim Smith 
#include "World.h"
#include "Renderer.h"
#include "Avatar.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "FirstPersonCameraT.h"
#include "OGFirstPersonCamera.h"
#include "BlenderModel.h"
#include "PortalEntrance.h"

#include "CubeModel.h"
#include "ModelGroup.h"

#include "Light.h"
#include "PointLight.h"

#include <GLFW/glfw3.h>
#include "EventManager.h"
#include "ThirdPersonCamera.h"
#include "Portal.h"
using namespace std;
using namespace glm;

World::World()
{
	//Avatar * avatar = new Avatar(glm::vec3(0.0f,1.0f,1.0f));
	CubeModel * cubeycube = new CubeModel();
	//addModel(cubeycube);
	Avatar * avatar = new Avatar(glm::vec3(0.0f,1.0f,1.0f));
	avatar->setCollisionBoxSize(glm::vec3(1.0f,1.0f,1.0f));
	addModel(avatar);
	colAv = avatar;

	CubeModel *cm = new CubeModel(glm::vec3(1.0f,1.0f,1.0f));
	cm->SetPosition(glm::vec3(10.0f,0.0f,0.0f));
	cm->setCollisionBoxSize(glm::vec3(1.0f));
	addModel(cm);

	colCube = cm;

	FirstPersonCamera * myt = new FirstPersonCamera(vec3(0.5f, 0.5f, 5.0f),cubeycube);
	// Setup Camera
	mCamera.push_back( new StaticCamera( vec3(3.0f, 4.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) ) );
	mCamera.push_back( new OGFirstPersonCamera(vec3(0.5f, 0.5f, 5.0f)));

	mCamera.push_back( new ThirdPersonCamera( vec3(3.0f, 4.0f, 5.0f),avatar ) );

	std::vector<glm::vec3> path;


	path.push_back(glm::vec3(0.0f,0.0f,0.0f));
	path.push_back(glm::vec3(10.0f,0.0f,0.0f));
	path.push_back(glm::vec3(20.0f,0.0f,0.0f));
	path.push_back(glm::vec3(30.0f,0.0f,1.0f));
	path.push_back(glm::vec3(40.0f,0.0f,1.0f));
	path.push_back(glm::vec3(50.0f,0.0f,1.0f));
	path.push_back(glm::vec3(60.0f,0.0f,1.0f));
	path.push_back(glm::vec3(70.0f,0.0f,1.0f));

	Portal* p = new Portal(path, 1.0f, 12);
//	addModel(p);
	myt->FollowPath(path);

	mCurrentCamera = 1;

	/*
	BlenderModel* blender = new BlenderModel("../Source/blender/sofa.obj","../Source/blender/sofa.dds");
	blender->SetPosition(glm::vec3(1,1,1));
	blender->SetScaling(glm::vec3(0.01f,0.01f,0.01f));
	addModel(blender);
	*/
	mCurrentCamera = 2;


	///portal thing
	PortalEntrance * PEntr = new PortalEntrance(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),10);
	addModel(PEntr);


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

	if(colAv->collides(colCube))
		std::cout<<"collide!";

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

	// Num keys to change shader (don't do this, it doesn't work) -Louis
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_8 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_PHONG);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_7 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_IMAGE);
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

	/**
	 * Lights remain consistent for entirety of world-draw, therefore,
	 * no need to redeclare this stuff under each model-loop iteration.
	 */

	int mLightSize = mLight.size();

	// Declare the pointers referencing the arrays holding each light property.
	GLfloat* lightPositions    = new GLfloat[mLightSize * 4]; // vec4 lightPosition
	GLfloat* lightColors       = new GLfloat[mLightSize * 3]; // vec3 lightColor
	GLfloat* lightCoefficients = new GLfloat[mLightSize * 3]; // vec3 lightCoefficient

	// Populate our arrays with the appropriate values.
	for (int i = 0; i < mLightSize; ++i)
	{
		/** 
		 * Using a linear list of assignment operations rather than multiple
		 * loops; should result in slightly better performance considering this
		 * gets called for every frame and we have fixed sizes anyways.
		 */

		// Fill up `lightPositions` (vec4 per light)
		lightPositions[(i*4)]   = mLight[i]->GetLightPosition().x;
		lightPositions[(i*4)+1] = mLight[i]->GetLightPosition().y;
		lightPositions[(i*4)+2] = mLight[i]->GetLightPosition().z;
		lightPositions[(i*4)+3] = mLight[i]->GetLightPosition().w;

		// Fill up `lightColors` (vec3 per light)
		lightColors[(i*3)]   = mLight[i]->GetLightColor().r;
		lightColors[(i*3)+1] = mLight[i]->GetLightColor().g;
		lightColors[(i*3)+2] = mLight[i]->GetLightColor().b;

		// Fill up `lightCoefficients` (vec3 per light)
		lightCoefficients[(i*3)]   = mLight[i]->GetLightCoefficients().x;
		lightCoefficients[(i*3)+1] = mLight[i]->GetLightCoefficients().y;
		lightCoefficients[(i*3)+2] = mLight[i]->GetLightCoefficients().z;
	}

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Get a convenient handler to our model pointer
		Model* model = *it;

		// Get the model's program ID
		unsigned int program = model->GetShaderProgramID();

		// Use the appropriate model shader program.
		glUseProgram(program);

		// Create the uniforms containing our transformation matrices
		GLuint VPMatrixLocation       = glGetUniformLocation(program, "ViewProjectonTransform");
		GLuint ViewTransformUniformID = glGetUniformLocation(program, "ViewTransform");
		GLuint ProjTransformUniformID = glGetUniformLocation(program, "ProjectonTransform");

		// Create the uniform IDs for a material attribute and our light attributes
		GLuint sMaterialUniformID		   = glGetUniformLocation(program, "materialCoefficients");
		GLuint sNumLightsUniformID		   = glGetUniformLocation(program, "NumLights");
		GLuint sLightPositionsUniformID	   = glGetUniformLocation(program, "LightPositions");
		GLuint sLightColorsUniformID	   = glGetUniformLocation(program, "LightColors");
		GLuint sLightCoefficientsUniformID = glGetUniformLocation(program, "LightAttenuations");

		// Send the view projection constants to the shader
		mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);
		glUniformMatrix4fv(ViewTransformUniformID, 1, GL_FALSE, &mCamera[mCurrentCamera]->GetViewMatrix()[0][0]);
		glUniformMatrix4fv(ProjTransformUniformID, 1, GL_FALSE, &mCamera[mCurrentCamera]->GetProjectionMatrix()[0][0]);

		// Send the model material coefficients to the shader,
		glUniform4f(
			sMaterialUniformID,
			model->GetMaterialCoefficients().x,
			model->GetMaterialCoefficients().y,
			model->GetMaterialCoefficients().z,
			model->GetMaterialCoefficients().w
		);

		// Send the number of lights we have to the shader,
		glUniform1i(sNumLightsUniformID, mLightSize);

		// Send our arrays of light properties to the shader,
		glUniform4fv(sLightPositionsUniformID, mLightSize, lightPositions);
		glUniform3fv(sLightColorsUniformID, mLightSize, lightColors);
		glUniform3fv(sLightCoefficientsUniformID, mLightSize, lightCoefficients);
		
		// Draw model
		model->Draw();
	}

	Renderer::EndFrame();

	// Deallocate our arrays
	delete lightPositions;
	delete lightColors;
	delete lightCoefficients;
}
