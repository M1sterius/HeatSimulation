#pragma once

#include "Particle.hpp"
#include "glm.hpp"

struct Manifold
{   
    std::shared_ptr<Particle> p1;
    std::shared_ptr<Particle> p2;

    glm::vec2 normal;
    float penetrationDepth;

    Manifold();
    Manifold(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, const glm::vec2& normal, const float penetrationDepth);
    ~Manifold();
};

bool CheckCollision(const std::shared_ptr<Particle> p1, const std::shared_ptr<Particle> p2, Manifold& manifold);
void ResolveCollision(const Manifold& manifold);
