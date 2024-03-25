#include "SFML/Graphics.hpp"
#include "glm.hpp"

#include "Particle.hpp"
#include "Scene.hpp"

#include <iostream>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Heat Simulation!");
    window.setFramerateLimit(165);

    Scene scene = Scene();

    std::shared_ptr<Particle> particle = std::make_shared<Particle>(30);
    particle->SetPosition(glm::vec2(100, 1));

    std::shared_ptr<Particle> particle1 = std::make_shared<Particle>(30);
    particle1->SetPosition(glm::vec2(110, 100));

    scene.AddParticle(particle);
    scene.AddParticle(particle1);

    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            std::shared_ptr<Particle> particle = std::make_shared<Particle>(10);
            particle->SetPosition(glm::vec2(i, j) * 80.0f);
            particle->SetVelocity(glm::vec2(1, 1) * 100.0f);
            scene.AddParticle(particle);
        }
        
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        scene.Update();
        scene.Render(window);

        window.display();
    }

    std::cin.get();

    return 0;
}
