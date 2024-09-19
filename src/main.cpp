#include "SFML/Graphics.hpp"
#include "glm.hpp"

#include "Particle.hpp"
#include "Scene.hpp"

#include <iostream>
#include <memory>
#include <math.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "Heat Simulation!");
    window.setFramerateLimit(240);

    Scene scene = Scene(700, 700);

    // Create an array of x * y particles
    for (size_t x = 0; x < 100; x++)
    {
        for (size_t y = 0; y < 35; y++)
        {
            Particle* particle = new Particle(3);
            particle->SetTemperature(10.0f);
            particle->SetPosition(glm::vec2(0, 350) + glm::vec2(x, y) * 7.0f);
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

    return 0;
}
