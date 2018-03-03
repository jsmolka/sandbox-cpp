#include "Snake.hpp"

Snake::Snake(int width, int height, int scale)
{
    srand(time(NULL));

    mDirection = east;
    mWindowWidth = width;
    mWindowHeight = height;
    mWindowScale = scale;

    mApple.setSize(sf::Vector2f(scale, scale));
    mApple.setFillColor(sf::Color::Red);
    deployApple();

    sf::RectangleShape head;
    head.setSize(sf::Vector2f(scale, scale));
    head.setFillColor(sf::Color::Green);
    mParts.emplace_back(head);
}

void Snake::move()
{
    update();

    sf::RectangleShape first;
    first.setSize(sf::Vector2f(mWindowScale, mWindowScale));
    first.setFillColor(sf::Color::Green);

    sf::Vector2f position = mParts[0].getPosition();
    if (mDirection == north)
        position.y -= mWindowScale;
    if (mDirection == south)
        position.y += mWindowScale;
    if (mDirection == east)
        position.x += mWindowScale;
    if (mDirection == west)
        position.x -= mWindowScale;

    first.setPosition(position);
    mParts.insert(mParts.begin(), first);
    mParts.pop_back();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = NULL;
    for (const auto &obj : mParts)
        target.draw(obj, states);
    target.draw(mApple, states);
}

void Snake::setDirection(direction dir)
{
    mDirection = dir;
}

bool Snake::appleInSnake()
{
    for (auto &m_part : mParts)
        if (m_part.getPosition().x == mApple.getPosition().x && m_part.getPosition().y == mApple.getPosition().y)
            return true;
    return false;
}

void Snake::generateApple()
{
    int rand_x = (rand() % mWindowWidth) * mWindowScale;
    int rand_y = (rand() % mWindowHeight) * mWindowScale;
    mApple.setPosition(rand_x, rand_y);
}

void Snake::deployApple()
{
    generateApple();
    while (appleInSnake())
        generateApple();
}

bool Snake::headInSnake()
{
    for (int i = 1; i < mParts.size(); i++)
        if (mParts[0].getPosition().x == mParts[i].getPosition().x &&
            mParts[0].getPosition().y == mParts[i].getPosition().y)
            return true;
    return false;
}

void Snake::update()
{
    if (appleInSnake())
    {
        sf::RectangleShape part;
        part.setPosition(mApple.getPosition());
        part.setSize(sf::Vector2f(mWindowScale, mWindowScale));
        part.setFillColor(sf::Color::Green);
        mParts.emplace_back(part);
        deployApple();
    }
}

bool Snake::gameOver()
{
    return mParts[0].getPosition().x < 0 ||
           mParts[0].getPosition().y < 0 ||
           mParts[0].getPosition().x == mWindowWidth * mWindowScale ||
           mParts[0].getPosition().y == mWindowHeight * mWindowScale ||
           headInSnake();
}
