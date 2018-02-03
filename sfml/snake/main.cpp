#include <iostream>
#include "Snake.hpp"

int main()
{
    const int WIDTH = 50;
    const int HEIGHT = 30;
    const int SCALE = 20;
    const float MOVE = 0.075;

    sf::RenderWindow window(sf::VideoMode(WIDTH * SCALE, HEIGHT * SCALE), "Snake");

    while (window.isOpen())
    {
        sf::Clock clock;
        float total = 0;
        Snake snake(WIDTH, HEIGHT, SCALE);

        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::R) && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    snake.setDirection(north);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    snake.setDirection(south);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    snake.setDirection(east);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    snake.setDirection(west);
            }

            if (!snake.gameOver())
            {
                window.clear();
                total += clock.restart().asSeconds();
                if (total >= MOVE)
                {
                    snake.move();
                    total = 0;
                }
                window.draw(snake);
                window.display();
            }
        }
    }
    return 0;
}