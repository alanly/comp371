#pragma once
#include "glm/glm.hpp"
#include "Random.h"
#include "PlaneModel.h"
#include <vector>

class Particle : public PlaneModel
{
public:
    Particle(glm::vec3 position, float minLife, float maxLife);
    // Take randRange to set starting position

    virtual void Update(float dt);
    // increase age by each frame, increase size? if a thing
    virtual void Draw();

    void ResetAge();

    glm::vec3 p_Velocity; //Particle's speed
    float     p_Rotate;   //Particle local Rotation on Z-Axis
    float     p_Age;      //Particle's age/duration since birth
    float     p_Lifetime; //Particle's lifespan
    float     p_Size;     //Particle's size in world
};
