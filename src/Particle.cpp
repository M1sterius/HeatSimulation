#include "Particle.hpp"
#include "PhysicsUtility.hpp"

#include <algorithm>

sf::Color Particle::GetTemperatureColor()
{
    const static sf::Color MAX_COLOR = sf::Color(255, 85, 0);

    const float t = std::clamp(m_Temperature / 100.0f, 0.0f, 1.0f);
    
    const int r = static_cast<int>(MAX_COLOR.r * t);
    const int g = static_cast<int>(MAX_COLOR.g * t);
    const int b = static_cast<int>(MAX_COLOR.b * t);

    return sf::Color(r, g, b);
}

Particle::Particle(const float& radius)
{   
    m_CurrentPosition = glm::vec2(0, 0);
    m_OldPosition = glm::vec2(0, 0);
    m_Acceleration = glm::vec2(0, 0);
    m_Radius = radius;
    
    m_Shape = sf::CircleShape(radius);
    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
    m_Shape.setFillColor(GetTemperatureColor());
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

    // Adjust the position of sfml shape so m_CurrentPosition is in it's center
    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
}

void Particle::Accelerate(const glm::vec2& accel)
{
    m_Acceleration += accel;
}

void Particle::SetTemperature(const float temperature)
{
    m_Temperature = temperature;
    m_Shape.setFillColor(GetTemperatureColor());
}

void Particle::SetPosition(const glm::vec2& nPos)
{
    const glm::vec2 diff = m_CurrentPosition - m_OldPosition;
    m_OldPosition = nPos;
    m_CurrentPosition = nPos + diff;

    // Adjust the position of sfml shape so m_CurrentPosition is in it's center
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
