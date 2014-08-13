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

    class Particle
    {
    public:
        Particle()
            : p_Position(0)
            , p_Velocity(0)
            , p_Color(0)
            , p_Rotate(0)
            , p_Age(0)
            , p_Lifetime(0)
        {}

        virtual void Update();
        virtual void Draw();

    private:
       glm::vec3 p_Position; //Particle center point
       glm::vec3 p_Velocity; //Particle's speed
       glm::vec4 p_Color;    //Particle's Color
       float     p_Rotate;   //Particle local Rotation on Z-Axis
       float     p_Age;      //Particle's age/duration since birth
       float     p_Lifetime; //Particle's lifespan
       float     p_Size;     //Particle's size in world

        unsigned char * textureImage;
    };

    typedef std::vector<Particle> ParticleBuffer;
};