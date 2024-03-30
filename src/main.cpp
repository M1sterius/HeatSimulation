#include "SFML/Graphics.hpp"
#include "glm.hpp"

#include "Particle.hpp"
#include "Scene.hpp"

#include <iostream>
#include <memory>
#include <math.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Heat Simulation!");
    window.setFramerateLimit(240);

    Scene scene = Scene(1280, 720);

    for (size_t i = 0; i < 63; i++)
    {
        Particle* particle = new Particle(10);
        particle->SetPosition(glm::vec2(20, 710) + glm::vec2(i, 0) * 20.0f);
        particle->SetTemperature(300.0f);
        particle->isStatic = true;
        particle->isConstHeat = true;
        scene.AddParticle(particle);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            Particle* particle = new Particle(5);
            particle->SetPosition(glm::vec2(mousePosition.x, mousePosition.y));
            scene.AddParticle(particle);
        }

        scene.Update();
        scene.Render(window);

        window.display();
    }

    std::cin.get();

    return 0;
}
