/*
 * @author Tiffany Ip
 */
#include "Particle.h"

Particle::Particle(glm::vec3 position, float minLife, float maxLife)
{
    SetPosition(position);

    // Random
    float pX = ((float)rand()/(float)(RAND_MAX)) - 0.5f;
    float pY = ((float)rand()/(float)(RAND_MAX)) - 0.5f;
    float pZ = ((float)rand()/(float)(RAND_MAX)) - 0.5f;

    // Set Velocity, Age, Lifetime
    p_Velocity = glm::vec3(pX, pY, pZ);
    p_Velocity = glm::normalize(p_Velocity) * 0.1f; //to go further
    p_Age = 0;
    p_Lifetime = RandRange(minLife, maxLife); 
}

void Particle::Update(float dt)
{
    p_Age += dt;

    // Direction vector
    SetPosition(GetPosition()+p_Velocity);
}

void Particle::ResetAge()
{
    p_Age = 0;
}