#pragma once

#include "SFML/Graphics.hpp"
#include "glm.hpp"

class Particle
{
private:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;

    float m_Radius;
    sf::CircleShape m_Shape;
public:
    Particle(const float& radius);
    ~Particle();

    void SetPosition(const glm::vec2& nPos);
    void SetVelocity(const glm::vec2& nVel);

    void AddPosition(const glm::vec2& pos);
    void AddVelocity(const glm::vec2& vel);

    inline glm::vec2 GetPosition() const { return m_Position; }
    inline glm::vec2 GetVelocity() const { return m_Velocity; }
    
    inline float GetRadius() const { return m_Radius; }

    const sf::CircleShape& GetShape() const;
};
