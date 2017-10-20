#include <iostream>
#include <ctime>
#include <SFML/System.hpp>

void delay(int seconds)
{
    time_t start, current;
    time(&start);
    do
    {
        time(&current);
    }
    while ((current - start) < seconds);
}

int main()
{
    sf::Time t1 = sf::microseconds(10000);
    sf::Time t2 = sf::milliseconds(100);
    sf::Time t3 = sf::seconds(0.01f);

    sf::Clock clock;
    delay(5);
    sf::Time t4 = clock.getElapsedTime();
    std::cout << t4.asSeconds() << std::endl;
    std::cout << t4.asMilliseconds() << std::endl;
    std::cout << t4.asMicroseconds() << std::endl;
};

