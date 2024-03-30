#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"
#include "glm.hpp"

bool SolveCollision(Particle* p1, Particle* p2);
void ConductHeat(Particle* p1, Particle* p2);
sf::Color GetTemperatureColor(float temp);