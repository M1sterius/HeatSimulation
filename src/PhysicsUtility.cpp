#include "PhysicsUtility.hpp"

#include <iostream>
#include <memory>
#include <math.h>

Manifold::Manifold()
{
    
}

Manifold::Manifold(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, const glm::vec2& normal, const float penetrationDepth)
    : p1(p1), p2(p2), normal(normal), penetrationDepth(penetrationDepth)
{
    
}

Manifold::~Manifold()
{
    
}

bool SolveCollision(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
    float d = glm::distance(p1->GetPosition(), p2->GetPosition());
    float rs = p1->GetRadius() + p2->GetRadius();
    glm::vec2 n = glm::normalize(p2->GetPosition() - p1->GetPosition());
    float delta = rs - d;

    if (d < rs)
    {
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

void ConductHeat(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
    float t1 = p1->GetTemperature();
    float t2 = p2->GetTemperature();

    float av = (t1 + t2) / 2;

    if (!p1->isConstHeat)
        p1->SetTemperature(std::lerp(t1, av, p1->heatTransferCoeff));
    if (!p2->isConstHeat)
        p2->SetTemperature(std::lerp(t2, av, p2->heatTransferCoeff));
}

sf::Color GetTemperatureColor(float temp)
{   
    const sf::Color MAX_COLOR = sf::Color(255, 85, 0);

    float t = std::max(0.0f, temp / 100.0f);

    int r = static_cast<int>(MAX_COLOR.r * t);
    int g = static_cast<int>(MAX_COLOR.g * t);
    int b = static_cast<int>(MAX_COLOR.b * t);

    return sf::Color(r, g, b);
}
