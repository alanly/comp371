//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//
/**
 * @author Alan Ly (multiple scene-lighting, per-model shaders)
 * Written by Thomas Rahn, Tim Smith 
 */
#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Camera;
class Model;
class Light;
class Avatar;
class CubeModel;
class PortalEntrance;
class FirstPersonCamera;
class SpiralModel;
class Portal;
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

private:
	std::vector<Model*> mModel;
	GLuint tex;
	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;
	FirstPersonCamera* fpc;
	Avatar* colAv;
	CubeModel* colCube;
	PortalEntrance * entr;
	std::vector<Light*> mLight;
	SpiralModel* spiral;
	Portal* portal;
	std::vector<glm::vec3> path;
};
