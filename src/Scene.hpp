#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.hpp"
#include "Grid.hpp"

#include <vector>
#include <memory>

class Scene
{
private:
    const size_t SUBSTEPS = 4;

    float m_DeltaTime = 0;

    std::vector<Particle*> m_Particles;

    size_t m_WinSizeX;
    size_t m_WinSizeY;
    Grid m_Grid;

    sf::Font m_DebugFont;
    sf::Text m_DebugText;

    void UpdateParticles(const float dt);
    void CheckBounds();
public:
    Scene(size_t winSizeX, size_t winXizeY);
    ~Scene();

    void AddParticle(Particle* ptr);

    void Update();
    void Render(sf::RenderWindow& window);

    inline size_t GetParticlesCount() const {return m_Particles.size(); }
};
