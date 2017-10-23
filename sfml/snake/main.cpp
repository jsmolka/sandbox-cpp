#include <cstdlib>
#include <iostream>
#include "Snake.hpp"

int main() {
    unsigned int WIDTH;
    unsigned int HEIGHT;
    unsigned int SCALE;
    unsigned int FRAMERATE;
    std::cout << "Width: ";
    std::cin >> WIDTH;
    std::cout << "Height: ";
    std::cin >> HEIGHT;
    std::cout << "Scale: ";
    std::cin >> SCALE;
    std::cout << "Framerate: ";
    std::cin >> FRAMERATE;

    sf::RenderWindow window(sf::VideoMode(WIDTH * SCALE, HEIGHT * SCALE), "Snake");
    window.setFramerateLimit(FRAMERATE);

    while (window.isOpen())
    {
        Snake snake(WIDTH, HEIGHT, SCALE);
        bool print_score = true;

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
                snake.move();
                window.draw(snake);
                window.display();
            }
            else
            {
                if (print_score)
                {
                    std::cout << "Game Over" << std::endl;
                    std::cout << "Score " << snake.getScore() << std::endl;
                    std::cout << "Press R to start a new game!" << std::endl;
                    print_score = false;
                }
            }
        }
    }

    return 0;
}