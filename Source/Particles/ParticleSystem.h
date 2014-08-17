#pragma once

#include "Model.h"
#include "Renderer.h"
#include "Particle.h"
#include <vector>
using namespace std;
class ParticleSystem : public Model
{
public:
        ParticleSystem(unsigned int numParticles);
        ~ParticleSystem();

        virtual void Update(float dt);
        virtual void Draw(); //linear iteration of vector pParticles
private:

    int numOfParticles;
    float lifespan;

    std::vector<Particle*> pParticles;
};