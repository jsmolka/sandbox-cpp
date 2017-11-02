#include <iostream>
#include <SFML/Graphics.hpp>

#include "FpsCounter.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Show FPS");
    FpsCounter fpsCounter(sf::Vector2f(0, 0), sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        fpsCounter.update();

        window.clear();
        window.draw(fpsCounter);
        window.display();
    }
    return 0;
}