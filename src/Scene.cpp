#include "Scene.hpp"
#include "PhysicsUtility.hpp"

#include <memory>
#include <iostream>
#include <math.h>

Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

void Scene::AddParticle(const std::shared_ptr<Particle> ptr)
{
    m_Particles.push_back(ptr);
}

void Scene::Update()
{
    static sf::Clock deltaTimeClock;

    // Integration ---------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {   
        std::shared_ptr<Particle> particle = m_Particles[i];
        particle->Accelerate(glm::vec2(0, 500));
        particle->Integrate(m_DeltaTime);
    }
    // ---------------------------------------------

    // Bounds --------------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        std::shared_ptr<Particle> particle = m_Particles[i];
        const glm::vec2 vertBounds = glm::vec2(0, 1280);
        const glm::vec2 horizBounds = glm::vec2(0, 720);

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

    // Collisions ----------------------------------
    for (size_t i = 0; i < m_Particles.size() - 1; i++)
    {
        for (size_t j = i + 1; j < m_Particles.size(); j++)
        {
            std::shared_ptr<Particle> p1 = m_Particles[i];
            std::shared_ptr<Particle> p2 = m_Particles[j];

            Manifold mf;

            SolveCollision(p1, p2);
        }
    }
    // ---------------------------------------------
    
    //std::cout << 1 / m_DeltaTime << '\n';
    m_DeltaTime = deltaTimeClock.restart().asSeconds();
}

void Scene::Render(sf::RenderWindow& window)
{
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        std::shared_ptr<Particle> particle = m_Particles[i];
        window.draw(particle->GetShape());
    }
}
