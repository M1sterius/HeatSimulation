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

    for (size_t i = 0; i < 65; i++)
    {
        Particle* particle = new Particle(10);
        particle->SetPosition(glm::vec2(0, 710) + glm::vec2(i, 0) * 20.0f);
        particle->SetTemperature(100.0f);
        particle->isStatic = true;
        particle->isConstHeat = true;
        scene.AddParticle(particle);
    }

    for (size_t x = 0; x < 200; x++)
    {
        for (size_t y = 0; y < 25; y++)
        {
            Particle* particle = new Particle(3);
            particle->SetTemperature(10.0f);
            particle->SetPosition(glm::vec2(140, 350) + glm::vec2(x, y) * 5.0f);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            Particle* particle = new Particle(3);
            particle->SetPosition(glm::vec2(mousePosition.x, mousePosition.y));
            scene.AddParticle(particle);
        }

        for (size_t i = 0; i < 4; i++)
        {
            scene.Update();
        }
        
        scene.Render(window);

        window.display();
    }

    std::cin.get();

    return 0;
}
