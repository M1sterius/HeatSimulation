#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"
#include "glm.hpp"

// Global physics parameters -------------------
const glm::vec2 g = glm::vec2(0, 981);
const float t_surroundings = 0.0f;
const float heat_loss_coefficient = 0.02f; // determines how fast objects will lose heat to the surroundings
const float thermal_expansion_coefficient = 0.07f; // determines how much upword force the heat will produce
// ---------------------------------------------

bool SolveCollision(Particle* p1, Particle* p2);

void ConductHeat(Particle* p1, Particle* p2, const float dt);
void ApplyConvection(Particle* p, const float dt);
void ApplyCooling(Particle* p, const float dt);
