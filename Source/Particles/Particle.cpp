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

    //Set random rotation
    SetRotation(glm::vec3(RandRange(0,1), RandRange(0,1),RandRange(0,1)), 45.0f);

    // Set Velocity, Age, Lifetime
    p_Velocity = glm::vec3(pX, pY, pZ);
    p_Velocity = glm::normalize(p_Velocity) * 0.5f; //to go further, use bigger numbers, otherwise small distance 0.01f
    p_Age = 0;
    p_Lifetime = RandRange(minLife, maxLife);
}

void Particle::Update(float dt)
{
    p_Age += dt;

    // Direction vector
    SetPosition(GetPosition() + p_Velocity);
}

void Particle::ResetAge()
{
    p_Age = 0;
}