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
        particle->AddVelocity(glm::vec2(0, 981 * m_DeltaTime));
        particle->AddPosition(particle->GetVelocity() * m_DeltaTime);
    }   
    // ---------------------------------------------

    // Bounds --------------------------------------
    for (size_t i = 0; i < m_Particles.size(); i++)
    {
        std::shared_ptr<Particle> particle = m_Particles[i];
        if (particle->GetPosition().y > 700)
        {   
            float pd = particle->GetPosition().y - 700;
            particle->SetPosition(particle->GetPosition() - glm::vec2(0, pd));
            particle->SetVelocity(-particle->GetVelocity() * 0.8f);
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
