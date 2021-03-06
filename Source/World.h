//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//
/**
 * @author Alan Ly (multiple scene-lighting, per-model shaders, multiple subreddits)
 * @author Thomas Rahn
 * @author Tiffany Ip (added particle system)
 */
#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CaptionImageSet.h"


class Camera;
class Model;
class Light;
class Avatar;
class CubeModel;
class PortalEntrance;
class FirstPersonCamera;
class SpiralModel;
class Portal;
class ParticleSystem;
#include <GLM/glm.hpp>
class World
{
public:
	World();
	~World();
	
	void Update(float dt);
	void Draw();

	void addModel(Model* nModel);
	void addLight(Light* nLight);
	void removeModel(Model* model);
	bool contains(Model* model);

private:
	std::vector<Model*> mModel;
	GLuint tex;
	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;
	FirstPersonCamera* fpc;
	Model* colAv;
	PortalEntrance * entr;
	std::vector<Light*> mLight;
	Portal* portal;
	std::vector<SpiralModel*> wSpirals;
	unsigned int wCurrentSpiral;
    ParticleSystem* particleSystem;
	std::vector<glm::vec3> path;
	std::vector<std::vector<CaptionImageSet*>> wImageSets;
	unsigned int wCurrentImageSet;
	void createPortalAndEntrance();
	void setUpCameras();
	void setupImageSets();
};
