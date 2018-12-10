#include <iostream>
#include <SFML/Graphics.hpp>

#include "fpscounter.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Show FPS");
    window.setFramerateLimit(120);
    FpsCounter fpsCounter(sf::Vector2f(0, 0));

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
