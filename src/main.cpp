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
    particle1->SetPosition(glm::vec2(1180, 1));

    scene.AddParticle(particle);
    scene.AddParticle(particle1);

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
