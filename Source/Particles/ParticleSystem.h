/*
 * @author Tiffany Ip
 */
#pragma once

#include "Model.h"
#include "Renderer.h"
#include "Particle.h"
#include "Image.h"
#include <vector>
using namespace std;
class ParticleSystem : public Model
{
public:
        ParticleSystem(unsigned int numParticles, Image* image, glm::vec3 position = glm::vec3(1.0));
        ~ParticleSystem();

        virtual void Update(float dt);
        virtual void Draw(); //linear iteration of vector pParticles
private:

    int numOfParticles;
    float lifespan;

    std::vector<Particle*> pParticles;
};