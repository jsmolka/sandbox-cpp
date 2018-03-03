#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

enum direction {north = 0, south = 1, east = 2, west = 3};

class Snake : public sf::Drawable, public sf::Transformable {
public:
    Snake(int width, int height, int scale);
    bool gameOver();
    void move();
    void setDirection(direction dir);
    void update();

private:
    bool appleInSnake();
    void deployApple();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void generateApple();
    bool headInSnake();

    int mWindowWidth;
    int mWindowHeight;
    int mWindowScale;
    direction mDirection;
    sf::RectangleShape mApple;
    std::vector<sf::RectangleShape> mParts;
};

#endif //SNAKE_SNAKE_HPP
