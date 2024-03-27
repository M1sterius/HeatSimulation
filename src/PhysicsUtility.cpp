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

void SolveCollision(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
    float d = glm::distance(p1->GetPosition(), p2->GetPosition());
    float rs = p1->GetRadius() + p2->GetRadius();
    glm::vec2 n = glm::normalize(p2->GetPosition() - p1->GetPosition());

    if (d < rs)
    {
        float delta = rs - d;
        p1->AddCurrentPosition(-0.5f * delta * n);
        p2->AddCurrentPosition(0.5f * delta * n);
    }
}
