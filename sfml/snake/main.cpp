#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include "Snake.hpp"

int main() {
    const unsigned int WIDTH = 50;
    const unsigned int HEIGHT = 30;
    const unsigned int SCALE = 20;
    const float REFRESH = 0.05;

    sf::RenderWindow window(sf::VideoMode(WIDTH * SCALE, HEIGHT * SCALE), "Snake");

    while (window.isOpen())
    {
        system("cls");
        sf::Clock clock;
        float total = 0;
        bool print_score = true;
        Snake snake(WIDTH, HEIGHT, SCALE);

        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
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
                if (total >= REFRESH)
                {
                    snake.move();
                    total = 0;
                }
                window.draw(snake);
                window.display();
            }
            else
            {
                if (print_score)
                {
                    std::cout << "Game Over" << std::endl;
                    std::cout << "Score " << snake.getScore() << std::endl;
                    print_score = false;
                }
            }
        }
    }
    return 0;
}