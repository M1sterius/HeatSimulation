#include "PhysicsUtility.hpp"

#include <iostream>
#include <memory>
#include <math.h>

// Global physics constants --------------------
const glm::vec2 g = glm::vec2(0, 981);
// ---------------------------------------------

bool SolveCollision(Particle* p1, Particle* p2)
{   
    const float COLLISION_COEFF = 0.8f;

    float d = glm::distance(p1->GetPosition(), p2->GetPosition());
    float rs = p1->GetRadius() + p2->GetRadius();
    glm::vec2 n = (p2->GetPosition() - p1->GetPosition()) / d;

    if (d < rs && d > 0.01f)
    {
        float delta = (rs - d) * COLLISION_COEFF;

        if (p1->isStatic)
        {
            p2->AddCurrentPosition(delta * n);
            return true;
        }
        else if (p2->isStatic)
        {
            p1->AddCurrentPosition(-delta * n);
            return true;
        }

        p1->AddCurrentPosition(-0.5f * delta * n);
        p2->AddCurrentPosition(0.5f * delta * n);
        return true;
    }

    return false;
}

void ConductHeat(Particle* p1, Particle* p2, const float dt)
{
    float t1 = p1->GetTemperature();
    float t2 = p2->GetTemperature();

    //float av = (t1 + t2) / 2;

    //if (!p1->isConstHeat)
    //    p1->SetTemperature(std::lerp(t1, av, p1->heatTransferCoeff));
    //if (!p2->isConstHeat)
    //    p2->SetTemperature(std::lerp(t2, av, p2->heatTransferCoeff));


    // float q = (k * 1.0f * (t2 - t1)) / glm::distance(p1->GetPosition(), p2->GetPosition());

    // p1->SetTemperature(t1 + (q / dt))
    float k = (p1->heatTransferCoeff + p2->heatTransferCoeff) / 2;

    float diff = t2 - t1;
    float q = k * diff;

    if (!p1->isConstHeat)
        p1->SetTemperature(t1 + (q * dt));
    if (!p2->isConstHeat)
        p2->SetTemperature(t2 - (q * dt));
}

void ApplyConvection(Particle* p, const float dt)
{

}

void ApplyCooling(Particle* p, const float dt)
{

}
