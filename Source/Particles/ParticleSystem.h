#pragma once

#include "Model.h"
#include "Renderer.h"
using namespace std;

class ParticleSystem : public Model
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
};