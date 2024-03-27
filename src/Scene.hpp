#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"

#include <vector>
#include <memory>

class Scene
{
private:
    float m_DeltaTime = 0;

    std::vector<std::shared_ptr<Particle>> m_Particles;
public:
    Scene();
    ~Scene();

    void AddParticle(const std::shared_ptr<Particle> ptr);

    void Update();
    void Render(sf::RenderWindow& window);

    inline size_t GetParticlesCount() const {return m_Particles.size(); }
};
