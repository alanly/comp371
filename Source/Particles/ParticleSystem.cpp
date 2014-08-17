#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int number)
{
    numOfParticles = number;
    for (unsigned int i = 0; i < number; i++)
    {
        float pX = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float pY = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float pZ = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float minLife = ((float)rand()/(float)(RAND_MAX)) * 0.6;
        float maxLife = ((float)rand()/(float)(RAND_MAX)) * 1.5;
        pParticles.push_back(new Particle(GetPosition()+glm::vec3(pX, pY, pZ), minLife, maxLife));
    }
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Update(float dt)
{
    for (unsigned int i=0; i < pParticles.size(); i++)
    {
        if (pParticles[i]->p_Age > pParticles[i]->p_Lifetime)
        {
            //Reset age, reset constructed position
            float pX = ((float)rand()/(float)(RAND_MAX)) * 0.5;
            float pY = ((float)rand()/(float)(RAND_MAX)) * 0.5;
            float pZ = ((float)rand()/(float)(RAND_MAX)) * 0.5;
            pParticles[i]->SetPosition(GetPosition()+glm::vec3(pX, pY, pZ));
            pParticles[i]->ResetAge();
        }
        pParticles[i]->Update(dt);
    }
}

void ParticleSystem::Draw()
{
    for (unsigned int i = 0 ; i < pParticles.size();  i++)
    {
        pParticles[i]->Draw();
    }
}