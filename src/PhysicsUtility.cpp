#include "PhysicsUtility.hpp"

#include <iostream>
#include <memory>
#include <math.h>

bool Collide(Particle* p1, Particle* p2)
{   
    const static float COLLISION_COEFF = 0.6f; // How much energy particles will keep after the collision

    const float rs = p1->GetRadius() + p2->GetRadius();
    const float d = glm::distance(p1->GetPosition(), p2->GetPosition());
    const glm::vec2 n = (p2->GetPosition() - p1->GetPosition()) / d;

    if (d < rs && d > 1.0f)
    {
        const float delta = (rs - d) * COLLISION_COEFF;

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
    const float t1 = p1->GetTemperature();
    const float t2 = p2->GetTemperature();

    const float k = 2 / ((1 / p1->heatTransferCoeff) + (1 / p2->heatTransferCoeff));

    const float diff = t2 - t1;
    const float q = k * diff;

    if (!p1->isConstHeat)
        p1->SetTemperature(t1 + (q * dt));
    if (!p2->isConstHeat)
        p2->SetTemperature(t2 - (q * dt));
}

void ApplyConvection(Particle* p, const float dt)
{   
    const float t = p->GetTemperature();

    const glm::vec2 f = g * t * THERMAL_EXPANSION_COEFFICIENT;

    p->Accelerate(-f);
}

void ApplyCooling(Particle* p, const float dt)
{
    if (p->isConstHeat)
        return;

    const float t = p->GetTemperature();

    const float diff = t - T_SURROUNDINGS;
    const float q = p->heatTransferCoeff * 1.0f * diff * HEAT_LOSS_COEFFICIENT;
    p->SetTemperature(t - (q * dt));
}
