#include <iostream>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Show FPS");
    sf::Clock clock;
    sf::Text fpsCounter;
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "Font not found" << std::endl;
    }
    fpsCounter.setFont(font);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setPosition(0, 0);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::stringstream ss;
        ss << std::trunc(1 / clock.restart().asSeconds());
        fpsCounter.setString(ss.str());

        window.clear();
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}