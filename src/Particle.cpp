#include "Particle.hpp"

Particle::Particle(const float& radius)
{   
    m_CurrentPosition = glm::vec2(0, 0);
    m_OldPosition = glm::vec2(0, 0);
    m_Acceleration = glm::vec2(0, 0);
    m_Radius = radius;
    
    m_Shape = sf::CircleShape(radius);
    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
}

Particle::~Particle()
{
    
}

void Particle::Integrate(const float dt)
{   
    if (isStatic)
        return;

    const glm::vec2 velocity = m_CurrentPosition - m_OldPosition;
    m_OldPosition = m_CurrentPosition;
    m_CurrentPosition = m_CurrentPosition + velocity + m_Acceleration * dt * dt;
    m_Acceleration = glm::vec2(0.0f, 0.0f);

    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
}

void Particle::Accelerate(const glm::vec2& accel)
{
    m_Acceleration += accel;
}

void Particle::SetPosition(const glm::vec2& nPos)
{
    glm::vec2 diff = m_CurrentPosition - m_OldPosition;
    m_OldPosition = nPos;
    m_CurrentPosition = nPos + diff;
    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
}

void Particle::AddPosition(const glm::vec2& pos)
{
    SetPosition(GetPosition() + pos);
}

void Particle::AddCurrentPosition(const glm::vec2& nPos)
{
    m_CurrentPosition += nPos;
}

glm::vec2 Particle::GetPosition()
{
    return m_CurrentPosition;
}

glm::vec2 Particle::GetVelocity()
{
    return m_CurrentPosition - m_OldPosition;
}

const sf::CircleShape& Particle::GetShape() const
{
    return m_Shape;
}
