#include "Particle.h"

Particle::Particle(glm::vec3 position, float minLife, float maxLife)
{
    SetPosition(position);

    // Random
    float pX = (((float)rand()/(float)(RAND_MAX)) * 1.0) - 0.5f;
    float pY = (((float)rand()/(float)(RAND_MAX)) * 1.0) - 0.5f;
    float pZ = (((float)rand()/(float)(RAND_MAX)) * 1.0) - 0.5f;

    //TODO set rotation to always face camera

    // Set Velocity, Age, Lifetime
    p_Velocity = glm::vec3(pX, pY, pZ);
    p_Velocity = glm::normalize(p_Velocity) * 0.01f;
    p_Age = 0;
    p_Lifetime = RandRange(minLife, maxLife); 
}

void Particle::Update(float dt)
{
    p_Age += dt;

    // Direction vector
    SetPosition(GetPosition()+p_Velocity);
}

void Particle::Draw()
{
    PlaneModel::Draw();
}

void Particle::ResetAge()
{
    p_Age = 0;
}