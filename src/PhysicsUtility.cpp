#include "PhysicsUtility.hpp"

#include <iostream>
#include <memory>

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

bool CheckCollision(const std::shared_ptr<Particle> p1, const std::shared_ptr<Particle> p2, Manifold& manifold)
{
    float d = glm::distance(p1->GetPosition(), p2->GetPosition());
    float rs = p1->GetRadius() + p2->GetRadius();

    if (d < rs)
    {   
        manifold.p1 = p1;
        manifold.p2 = p2;
        manifold.normal = glm::normalize(p2->GetPosition() - p1->GetPosition());
        manifold.penetrationDepth = rs - d;

        return true;
    }

    return false;
}

void ResolveCollision(const Manifold& manifold)
{   
    std::shared_ptr<Particle> p1 = manifold.p1;
    std::shared_ptr<Particle> p2 = manifold.p2;
    glm::vec2 normal = manifold.normal;

    glm::vec2 rv = p2->GetVelocity() - p1->GetVelocity();
    float rvAlongNormal = rv.x * normal.x + rv.y * normal.y;

    if (rvAlongNormal < 0)
    {
        float impulseMagnitude = -1.8f * rvAlongNormal / (1.0f / p1->mass + 1.0f / p2->mass);

        glm::vec2 impulse = impulseMagnitude * normal;

        p1->AddVelocity(-impulse / p1->mass);
        p2->AddVelocity(impulse / p2->mass);

        glm::vec2 separation = 0.5f * manifold.penetrationDepth * normal;
        p1->AddPosition(separation);
        p1->AddPosition(-separation);
    }
}




