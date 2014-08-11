#pragma once

#include "Model.h"
using namespace std;

class ParticleSystem : Model
{
public:
        ParticleSystem();
        ~ParticleSystem();

        virtual void Update(float lifespan);
        virtual void Draw();
private:

    int numOfParticles;
    float lifespan;

    glm::vec3 pMagnitude;
    glm::vec3 pParticles;

    unsigned char * textureImage;
};