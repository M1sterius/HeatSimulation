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
    window.setFramerateLimit(165);

    Scene scene = Scene();

    // sf::Font font;
    // font.loadFromFile("arial.ttf");

    // sf::Text text;
    // text.setFont(font);
    // text.setString("Test string!");
    // text.setCharacterSize(14);
    // text.setFillColor(sf::Color::Green);
    // text.setPosition(10, 10);

    // const size_t particlesNumber = 50;
    // for (size_t i = 0; i < std::round(std::sqrt(particlesNumber)); i++)
    // {
    //     for (size_t j = 0; j < std::round(std::sqrt(particlesNumber)); j++)
    //     {
    //         std::shared_ptr<Particle> particle = std::make_shared<Particle>(10);
    //         particle->SetPosition(glm::vec2(40, 40) + glm::vec2(i, j) * 40.0f);
    //         //particle->Accelerate(glm::vec2(1, 1) * 300.0f);
    //         scene.AddParticle(particle);
    //     }
    // }

    for (size_t i = 0; i < 31; i++)
    {
        std::shared_ptr<Particle> particle = std::make_shared<Particle>(10);
        particle->SetPosition(glm::vec2(40, 710) + glm::vec2(i, 0) * 40.0f);
        particle->SetTemperature(100.0f);
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
            std::shared_ptr<Particle> particle = std::make_shared<Particle>(10);
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
