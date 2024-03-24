#include "PhysicsUtility.hpp"

#include <iostream>

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
    std::cout << "Collide" << '\n';
}




