//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

/**
 * @author Alan Ly (multiple scene-lighting, per-model shaders)
 * @author Thomas Rahn (world update logic, camera/model initialization) 
 */
#include "World.h"
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Avatar.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "BlenderModel.h"
#include "PortalEntrance.h"
#include "CubeModel.h"
#include "ModelGroup.h"
#include "Light.h"
#include "PointLight.h"
#include "EventManager.h"
#include "ThirdPersonCamera.h"
#include "Portal.h"
#include "Model.h"
#include "SphereModel.h"
#include "PlaneModel.h"
#include "ParticleSystem.h"
#include "SOIL.h"
#include "LSystemModel.h"
#include "RectangleModel.h"
#include "ArcModel.h"
#include "Text2DModel.h"
#include "SpiralModel.h"

using namespace std;
using namespace glm;

World::World()
{
	colAv = new Avatar(glm::vec3(0.0f,1.0f,1.0f));
	colAv->SetPosition(glm::vec3(5.0f,5.0f,5.0f));
	colAv->setCollisionBoxSize(glm::vec3(1.0f,1.0f,1.0f));
	addModel(colAv);

	setUpCameras();

	setupImageSets();

  	wSpirals.push_back(new SpiralModel(glm::vec4(1.0f,0.0f,0.0f,1.0f) , //color
		     glm::vec4(0.0f,0.0f,1.0f,1.0f), //color2
			 glm::vec3(90.0f, 3.0f, 0.0f), //Position
			 glm::vec3(1.0f,0.0f,0.0f), //Normal (up vector)
			 glm::vec3(0.0f,0.0f,1.0f), //Binormal
			 2.0f, //Radius 1
			 4.0f, //Radius 2
			 360.0f * 7.5f, //Arc Angle
			 500,		//arbitrary # edges
			 15.0f, 	//arbitrary height	
			 wImageSets.at(0))
	);

	wSpirals.push_back(new SpiralModel(glm::vec4(1.0f,0.0f,0.0f,1.0f) , //color
		glm::vec4(0.0f,0.0f,1.0f,1.0f), //color2
		glm::vec3(90.0f, 3.0f, 0.0f), //Position
		glm::vec3(1.0f,0.0f,0.0f), //Normal (up vector)
		glm::vec3(0.0f,0.0f,1.0f), //Binormal
		2.0f, //Radius 1
		4.0f, //Radius 2
		360.0f * 7.5f, //Arc Angle
		500,		//arbitrary # edges
		15.0f, 	//arbitrary height	
		wImageSets.at(1))
	);

	wCurrentSpiral = 1;


	// Create and add our lighting to the world
	PointLight* light1 = new PointLight(glm::vec3(5.f, 0.f, 0.f));
	addLight(light1);

	PointLight* light2 = new PointLight(glm::vec3(5.f, -10.f, 0.f));
	addLight(light2);

	createPortalAndEntrance();

	
	//BlenderModel* blender = new BlenderModel("../Source/blender/snoo.obj","../Source/blender/snoo.dds");
	//blender->SetPosition(glm::vec3(1,0,1));
	//blender->SetScaling(glm::vec3(0.1f,0.1f,0.1f));
	////blender->SetShader(Renderer::LoadShaders( "../Source/Shaders/SimpleTransform.vertexshader", "../Source/Shaders/SingleColor.fragmentshader" ));
	//addModel(blender);

	//BlenderModel* blender2 = new BlenderModel("../Source/blender/sofa.obj","../Source/blender/sofa.dds");
	//blender2->SetPosition(glm::vec3(1,1,1));
	//blender2->SetScaling(glm::vec3(0.01f,0.01f,0.01f));
	//addModel(blender2);
	
}

World::~World()
{
	glDeleteTextures(1, &tex); //remove texture from openGL
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

	if(colAv->collides(entr)) {
		mCurrentCamera = 1;
		mModel.clear();

		fpc->FollowPath(path);
		addModel(portal);
		
		wCurrentSpiral = (wCurrentSpiral == 0) ? 1 : 0;
		addModel(wSpirals.at(wCurrentSpiral));

		entr->SetPosition(glm::vec3(90.0f,25.0f,0.0f));
		entr->SetRotation(glm::vec3(0,1.0f,0),90.0f);
		addModel(entr);	
	}

	if(!fpc->followPath){
		// User Inputs
		// 0 1 2 to change the Camera
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1 ) == GLFW_PRESS)
		{
			mCurrentCamera = 0;
			if(!contains(colAv)){
				addModel(colAv);
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2 ) == GLFW_PRESS)
		{
			if (mCamera.size() > 1)
			{
				mCurrentCamera = 1;
				removeModel(colAv);
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3 ) == GLFW_PRESS)
		{
			if (mCamera.size() > 2)
			{
				mCurrentCamera = 2;
				if(!contains(colAv)){
					addModel(colAv);
				}
			}
		}
		removeModel(portal);
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


bool World::contains(Model* model)
{
	for(int i = 0; i < mModel.size(); i++){
		if(model == mModel[i]){
			return true;
		}
	}
	return false;
}
void World::removeModel(Model* model)
{
	for(int i = 0; i < mModel.size(); i++){
		if(model == mModel[i]){
			mModel.erase(mModel.begin()+i);
		}
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

		SpiralModel* spM = dynamic_cast<SpiralModel*>(model);
		if(spM != 0) {
			// old was safely casted to NewType
			spM->DrawImages(mCamera[mCurrentCamera], mLightSize, lightPositions, lightColors, lightCoefficients);
		}
	}

	Renderer::EndFrame();

	// Deallocate our arrays
	delete lightPositions;
	delete lightColors;
	delete lightCoefficients;
}

void World::createPortalAndEntrance(){

	//set up path
	path.push_back(glm::vec3(5.0f,2.0f,0.0f));
	path.push_back(glm::vec3(7.0f,3.0f,0.0f));
	path.push_back(glm::vec3(12.0f,3.0f,2.0f));
	path.push_back(glm::vec3(15.0f,3.0f,2.0f));
	path.push_back(glm::vec3(20.0f,1.0f,0.0f));
	path.push_back(glm::vec3(24.0f,1.0f,2.0f));
	path.push_back(glm::vec3(28.0f,1.0f,0.0f));
	path.push_back(glm::vec3(30.0f, 2.0f, 0.0f));
	path.push_back(glm::vec3(35.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(36.0f, 3.0f, 0.0f));
	path.push_back(glm::vec3(37.0f, 3.0f, 0.0f));
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

	//create portal tube
	portal = new Portal(path, 1.0f, 12);

	///portal thing
	entr = new PortalEntrance(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),10);
	addModel(entr);
}

void World::setUpCameras(){
	fpc = new FirstPersonCamera(vec3(0.5f, 0.5f, 5.0f),colAv);
	mCamera.push_back( new StaticCamera( vec3(3.0f, 4.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) ) );
	mCamera.push_back( fpc);

	mCamera.push_back( new ThirdPersonCamera( vec3(3.0f, 4.0f, 5.0f),colAv ) );

	mCurrentCamera = 1;
}


void World::setupImageSets()
{
	printf("Loading image sets... ");
	/**
	 * Create the image set representing SUBREDDIT_1
	 */
	std::vector<CaptionImageSet*> subreddit_1;

	// Assign images for first subreddit
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/Scottish_Fold.jpg"), new Image("../Assets/ImageCaptions/scottish-fold.png") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/astrosloth.jpg"), new Image("../Assets/ImageCaptions/astrosloth.png") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/ball_catch.png") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/bankruptcy.png") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/born.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/buddy-cates.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/buddy-maus.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/bunneh.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/bunnehs.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/cate.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/cattie.jpg"), new Image("../Assets/ImageCaptions/cattie.png") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/creepy-cate.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/diabetes.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/doge-babeh.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/elefant.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/entertained.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/exit_butt.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/gerlic.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/grumpy.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/haha-business.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/harry-potter.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/heavy-breathing.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/herp-cate.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/hungry-cate.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/ice-cream.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/impressed.jpg") ));
	subreddit_1.push_back(new CaptionImageSet( new Image("../Assets/Images/jimmies.jpg") ));

	/**
	 * Create the image set representing SUBREDDIT_2
	 */
	std::vector<CaptionImageSet*> subreddit_2;

	// Assign images for second subreddit
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/king-cate.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/lab.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/littler-cate.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/mayor.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/not_bad_cheers.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/now_kith.jpg"), new Image("../Assets/ImageCaptions/now-kith.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/oh-shit-its-op.jpg"), new Image("../Assets/ImageCaptions/op.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/oh-you-dog.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/oh_stop.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/parents.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/poor-dan.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/priorities.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/rainbow.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/realisation_dog.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/science-bitch.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/seal.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/shit-itself.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/siblings.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/skwurl.png") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/soon.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/squids.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/steak-doge.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/tell-you-whut.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/tied.jpg") ));
	subreddit_2.push_back(new CaptionImageSet( new Image("../Assets/Images/what-is-cat.jpg") ));

	// Push the image sets
	wImageSets.push_back(subreddit_1);
	wImageSets.push_back(subreddit_2);

	printf("Loaded.\n");
}