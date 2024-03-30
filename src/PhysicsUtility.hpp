#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"
#include "glm.hpp"

// Global physics parameters -------------------
extern const glm::vec2 g;
// ---------------------------------------------

bool SolveCollision(Particle* p1, Particle* p2);

void ConductHeat(Particle* p1, Particle* p2, const float dt);
void ApplyConvection(Particle* p, const float dt);
void ApplyCooling(Particle* p, const float dt);
