#pragma once

#include "SFML/Graphics.hpp"
#include "glm.hpp"

class Particle
{
private:
    // Simulation uses Verlet integration
    glm::vec2 m_CurrentPosition;
    glm::vec2 m_OldPosition;
    glm::vec2 m_Acceleration;

    float m_Radius;
    sf::CircleShape m_Shape;

    float m_Temperature = 0.0f;
    
    sf::Color GetTemperatureColor();
public:
    // If true, particle will not be affected by any forces
    bool isStatic = false;
    // If true, particles will never lose any heat (but still can conduct it to other particles)
    bool isConstHeat = false;
    float heatTransferCoeff = 9.0f;

    Particle(const float& radius);
    ~Particle();

    void Integrate(const float dt);
    void Accelerate(const glm::vec2& accel);

    void SetTemperature(const float temperature);
    void SetPosition(const glm::vec2& nPos);
    void AddPosition(const glm::vec2& pos);
    void AddCurrentPosition(const glm::vec2& nPos);

    inline glm::vec2 GetPosition() const { return m_CurrentPosition; }
    inline glm::vec2 GetVelocity() const { return m_CurrentPosition - m_OldPosition; }
    inline float GetTemperature() const { return m_Temperature; }

    inline float GetRadius() const { return m_Radius; }

    const inline sf::CircleShape& GetShape() const { return m_Shape; }
};
