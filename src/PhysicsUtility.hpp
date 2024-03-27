#pragma once

#include "SFML/Graphics.hpp"
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

bool SolveCollision(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
void ConductHeat(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
sf::Color GetTemperatureColor(float temp);