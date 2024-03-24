#include "Particle.hpp"

Particle::Particle(const float& radius)
{   
    m_Position = glm::vec2(0, 0);
    m_Velocity = glm::vec2(0, 0);
    m_Radius = radius;
    
    m_Shape = sf::CircleShape(radius);
    m_Shape.setPosition(sf::Vector2f(m_Position.x - m_Radius, m_Position.y - m_Radius));
}

Particle::~Particle()
{
    
}

void Particle::SetPosition(const glm::vec2& nPos)
{
    m_Position = nPos;
    m_Shape.setPosition(sf::Vector2f(m_Position.x - m_Radius, m_Position.y - m_Radius));
}

void Particle::SetVelocity(const glm::vec2& nVel)
{
    m_Velocity = nVel;
}

void Particle::AddPosition(const glm::vec2& pos)
{
    SetPosition(m_Position + pos);
}

void Particle::AddVelocity(const glm::vec2& vel)
{
    SetVelocity(m_Velocity + vel);
}

const sf::CircleShape& Particle::GetShape() const
{
    return m_Shape;
}
