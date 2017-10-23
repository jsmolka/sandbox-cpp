#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle System");

    ParticleSystem particles(100000);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        window.clear();
        window.draw(particles);
        window.display();
    }
}