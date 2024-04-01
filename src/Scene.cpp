#include "Scene.hpp"
#include "PhysicsUtility.hpp"

#include <memory>
#include <iostream>
#include <math.h>

Scene::Scene(size_t winSizeX, size_t winSizeY)
    : m_WinSizeX(winSizeX), m_WinSizeY(winSizeY), m_Grid(winSizeX, winSizeY, 80)
{
    m_DebugFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    m_DebugText.setFont(m_DebugFont);
    m_DebugText.setCharacterSize(14);
    m_DebugText.setFillColor(sf::Color::White);
}

Scene::~Scene()
{
    
}

void Scene::AddParticle(Particle* ptr)
{
    m_Particles.push_back(ptr);
}

void Scene::Update()
{
    static sf::Clock deltaTimeClock;

    // Integration ---------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {   
        Particle* particle = m_Particles[i];
        particle->Accelerate(g);
        particle->Integrate(m_DeltaTime);

        ApplyConvection(particle, m_DeltaTime);
        ApplyCooling(particle, m_DeltaTime);
    }
    // ---------------------------------------------

    // Bounds --------------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        Particle* particle = m_Particles[i];
        const glm::vec2 vertBounds = glm::vec2(0, m_WinSizeX);
        const glm::vec2 horizBounds = glm::vec2(0, m_WinSizeY);

        glm::vec2 pos = particle->GetPosition();
        float r = particle->GetRadius();

        if (pos.x < (vertBounds.x + r))
        {
            glm::vec2 sep = glm::vec2((vertBounds.x + r) - pos.x, 0.0f);
            particle->AddCurrentPosition(sep);
        }
        if (pos.x > (vertBounds.y - r))
        {
            glm::vec2 sep = glm::vec2(pos.x - (vertBounds.y - r), 0);
            particle->AddCurrentPosition(-sep);
        }
        if (pos.y < (horizBounds.x + r))
        {
            glm::vec2 sep = glm::vec2(0, (horizBounds.x + r) - pos.y);
            particle->AddCurrentPosition(sep);
        }
        if (pos.y > (horizBounds.y - r))
        {
            glm::vec2 sep = glm::vec2(0, pos.y - (horizBounds.y - r));
            particle->AddCurrentPosition(-sep);
        }
    }
    // ---------------------------------------------

    // Updating the grid ---------------------------
    m_Grid.Update(m_Particles, m_DeltaTime);
    // ---------------------------------------------
    
    //std::cout << 1 / m_DeltaTime << ", " << m_Particles.size() << '\n';
    m_DeltaTime = deltaTimeClock.restart().asSeconds();
}

void Scene::Render(sf::RenderWindow& window)
{
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        Particle* particle = m_Particles[i];
        window.draw(particle->GetShape());
    }

    // Display debug info --------------------------
    m_DebugText.setString("FPS: " + std::to_string(1 / m_DeltaTime));
    m_DebugText.setPosition(10, 10);
    window.draw(m_DebugText);

    m_DebugText.setString("Prtcls: " + std::to_string(m_Particles.size()));
    m_DebugText.setPosition(10, 30);
    window.draw(m_DebugText);
    // ---------------------------------------------
}
