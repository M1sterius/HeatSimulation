#pragma once

#include "SFML/Graphics.hpp"
#include "glm.hpp"

class Particle
{
private:
    glm::vec2 m_CurrentPosition;
    glm::vec2 m_OldPosition;
    glm::vec2 m_Acceleration;

    float m_Radius;
    sf::CircleShape m_Shape;

    float m_Temperature = 30.0f;
    
public:
    bool isStatic = false;
    bool isConstHeat = false;
    float heatTransferCoeff = 0.6f;

    Particle(const float& radius);
    ~Particle();

    void Integrate(const float dt);
    void Accelerate(const glm::vec2& accel);
    void ApplyHeat(const float dt);

    void SetTemperature(const float temperature);
    void SetPosition(const glm::vec2& nPos);
    void AddPosition(const glm::vec2& pos);
    void AddCurrentPosition(const glm::vec2& nPos);

    glm::vec2 GetPosition();
    glm::vec2 GetVelocity();
    inline float GetTemperature() const { return m_Temperature; }

    inline float GetRadius() const { return m_Radius; }

    const sf::CircleShape& GetShape() const;
};
