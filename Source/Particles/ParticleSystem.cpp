/*
 * @author Tiffany Ip
 */
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int number, Image* image, glm::vec3 position)
{
    mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Image.vertexshader", "../Source/Shaders/Image.fragmentshader");
    numOfParticles = number;
    if (position != glm::vec3(1.0f)){
    SetPosition(position); //Set the position of the particle system if given
    }

    for (unsigned int i = 0; i < number; i++)
    {
        float pX = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float pY = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float pZ = ((float)rand()/(float)(RAND_MAX)) * 0.5;
        float minLife = 1.0f;//((float)rand()/(float)(RAND_MAX)) * 0.1;
        float maxLife = 10.0f;//((float)rand()/(float)(RAND_MAX)) * 2;
        Particle* newParticle = new Particle(GetPosition()+glm::vec3(pX, pY, pZ), minLife, maxLife);
        newParticle->SetShader(mShaderProgramID);
        newParticle->SetImage(image);
        pParticles.push_back(newParticle);
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