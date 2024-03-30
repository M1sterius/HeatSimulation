#include "Particle.hpp"
#include "PhysicsUtility.hpp"

#include <algorithm>

sf::Color Particle::GetTemperatureColor()
{
    const sf::Color MAX_COLOR = sf::Color(255, 85, 0);

    float t = std::min(1.0f, std::max(0.0f, m_Temperature / 100.0f));

    int r = static_cast<int>(MAX_COLOR.r * t);
    int g = static_cast<int>(MAX_COLOR.g * t);
    int b = static_cast<int>(MAX_COLOR.b * t);

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

    m_Shape.setPosition(sf::Vector2f(m_CurrentPosition.x - m_Radius, m_CurrentPosition.y - m_Radius));
}

void Particle::Accelerate(const glm::vec2& accel)
{
    m_Acceleration += accel;
}

void Particle::ApplyHeat(const float dt)
{   
    // Convection force
    float t = std::max(0.0f, m_Temperature / 100.0f);
    Accelerate(glm::vec2(0, -4300.0f) * t);

    // Cooling by the sorroundings
    if (isConstHeat)
        return;

    /*const float COOLING_RATE = 0.3f;
    float change = heatTransferCoeff * m_Temperature * COOLING_RATE * dt;
    SetTemperature(m_Temperature - change);*/

    float diff = 10 - m_Temperature;
    float q = heatTransferCoeff * 1.0f * diff;
    SetTemperature(m_Temperature + q * dt);
}

void Particle::SetTemperature(const float temperature)
{
    m_Temperature = temperature;
    m_Shape.setFillColor(GetTemperatureColor());
}

void Particle::SetPosition(const glm::vec2& nPos)
{
    glm::vec2 diff = m_CurrentPosition - m_OldPosition;
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
