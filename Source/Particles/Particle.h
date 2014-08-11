#pragma once

#include "ParticleSystem.h"
#include <GLM/glm.hpp>
using namespace std;

class Particle
{
public:
    Particle(ParticleSystem * pm);
    ~Particle();

    virtual void Update();
    virtual void Draw();

private:
    glm::vec3 particleSystemPosition;
    glm::vec3 particleCurrentPosition;

    float particleLifespan;

    unsigned char * textureImage;
};