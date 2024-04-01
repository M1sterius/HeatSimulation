#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"
#include "glm.hpp"

// Global physics parameters -------------------
const glm::vec2 g = glm::vec2(0, 981);
const float T_SURROUNDINGS = 0.0f;
const float HEAT_LOSS_COEFFICIENT = 0.1f; // determines how fast objects will lose heat to the surroundings
const float THERMAL_EXPANSION_COEFFICIENT = 0.045f; // determines how much upward force the heat will produce
// ---------------------------------------------

bool SolveCollision(Particle* p1, Particle* p2);

void ConductHeat(Particle* p1, Particle* p2, const float dt);
// Applies upward force based on the temperature of particle
void ApplyConvection(Particle* p, const float dt);
// Simulates cooling by the surroundings
void ApplyCooling(Particle* p, const float dt);
