#include "Scene.hpp"
#include "PhysicsUtility.hpp"

#include <memory>
#include <iostream>

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
        //particle->AddVelocity(glm::vec2(0, 981) * m_DeltaTime);
        particle->AddPosition(particle->GetVelocity() * m_DeltaTime);
    }
    // ---------------------------------------------

    // Bounds --------------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        std::shared_ptr<Particle> particle = m_Particles[i];
        const glm::vec2 vertBounds = glm::vec2(0, 1280);
        const glm::vec2 horizBounds = glm::vec2(0, 720);

        glm::vec2 pos = particle->GetPosition();
        glm::vec2 vel = particle->GetVelocity();
        float r = particle->GetRadius();

        if (pos.x < vertBounds.x + r)
        {
            particle->SetVelocity(glm::vec2(-vel.x, vel.y) * 0.8f);
            particle->AddPosition(glm::vec2(5, 0));
        }
        else if (pos.x > vertBounds.y - r)
        {
            particle->SetVelocity(glm::vec2(-vel.x, vel.y) * 0.8f);
            particle->AddPosition(glm::vec2(-5, 0));
        }
        else if (pos.y < horizBounds.x + r)
        {
            particle->SetVelocity(glm::vec2(vel.x, -vel.y) * 0.8f);
            particle->AddPosition(glm::vec2(0, 5));
        }
        else if (pos.y > horizBounds.y - r)
        {
            particle->SetVelocity(glm::vec2(vel.x, -vel.y) * 0.8f);
            particle->AddPosition(glm::vec2(0, -5));
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

            if (CheckCollision(p1, p2, mf))
                 ResolveCollision(mf);
        }
    }
    // ---------------------------------------------

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
