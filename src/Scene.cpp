#include "Scene.hpp"
#include "PhysicsUtility.hpp"

#include <memory>
#include <iostream>
#include <math.h>
#include <string>

Scene::Scene(size_t winSizeX, size_t winSizeY)
    : m_WinSizeX(winSizeX), m_WinSizeY(winSizeY), m_Grid(winSizeX, winSizeY, 70, m_Particles)
{   
    const static std::string FONT = "C:/Windows/Fonts/Arial.ttf";

    m_DebugFont.loadFromFile(FONT);
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

void Scene::UpdateParticles(const float dt)
{
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        Particle* particle = m_Particles[i];
        particle->Accelerate(g);
        particle->Integrate(dt);

        ApplyConvection(particle, dt);
        ApplyCooling(particle, dt);
    }
}

void Scene::CheckBounds()
{
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        Particle* particle = m_Particles[i];
        const glm::vec2 vertBounds = glm::vec2(0, m_WinSizeX);
        const glm::vec2 horizBounds = glm::vec2(0, m_WinSizeY);

        const glm::vec2 pos = particle->GetPosition();
        const float r = particle->GetRadius();

        glm::vec2 sep;

        if (pos.x < (vertBounds.x + r))
        {
            sep = glm::vec2((vertBounds.x + r) - pos.x, 0.0f);
            particle->AddCurrentPosition(sep);
        }
        if (pos.x > (vertBounds.y - r))
        {
            sep = glm::vec2(pos.x - (vertBounds.y - r), 0);
            particle->AddCurrentPosition(-sep);
        }
        if (pos.y < (horizBounds.x + r))
        {
            sep = glm::vec2(0, (horizBounds.x + r) - pos.y);
            particle->AddCurrentPosition(sep);
        }
        if (pos.y > (horizBounds.y - r))
        {
            sep = glm::vec2(0, pos.y - (horizBounds.y - r));
            particle->AddCurrentPosition(-sep);
            particle->SetTemperature(200.0f);
        }
    }
}

void Scene::Update()
{
    static sf::Clock deltaTimeClock;

    for (size_t i = 0; i < SUBSTEPS; i++)
    {   
        const float dt = m_DeltaTime / 4;

        UpdateParticles(dt);

        CheckBounds();

        m_Grid.Update(dt);
    }
    
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
