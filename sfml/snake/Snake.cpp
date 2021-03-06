#include "Snake.hpp"

Snake::Snake(int width, int height, int scale)
{
    srand(time(NULL));

    m_direction = east;
    m_windowWidth = width;
    m_windowHeight = height;
    m_windowScale = scale;

    m_apple.setSize(sf::Vector2f(scale, scale));
    m_apple.setFillColor(sf::Color::Red);
    deployApple();

    sf::RectangleShape head;
    head.setSize(sf::Vector2f(scale, scale));
    head.setFillColor(sf::Color::Green);
    m_parts.emplace_back(head);
}

void Snake::move()
{
    update();

    sf::RectangleShape first;
    first.setSize(sf::Vector2f(m_windowScale, m_windowScale));
    first.setFillColor(sf::Color::Green);

    sf::Vector2f position = m_parts[0].getPosition();
    if (m_direction == north)
        position.y -= m_windowScale;
    if (m_direction == south)
        position.y += m_windowScale;
    if (m_direction == east)
        position.x += m_windowScale;
    if (m_direction == west)
        position.x -= m_windowScale;

    first.setPosition(position);
    m_parts.insert(m_parts.begin(), first);
    m_parts.pop_back();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = NULL;
    for (const auto &obj : m_parts)
        target.draw(obj, states);
    target.draw(m_apple, states);
}

void Snake::setDirection(direction dir)
{
    m_direction = dir;
}

bool Snake::appleInSnake()
{
    for (auto &m_part : m_parts)
        if (m_part.getPosition().x == m_apple.getPosition().x && m_part.getPosition().y == m_apple.getPosition().y)
            return true;
    return false;
}

void Snake::generateApple()
{
    int rand_x = (rand() % m_windowWidth) * m_windowScale;
    int rand_y = (rand() % m_windowHeight) * m_windowScale;
    m_apple.setPosition(rand_x, rand_y);
}

void Snake::deployApple()
{
    generateApple();
    while (appleInSnake())
        generateApple();
}

bool Snake::headInSnake()
{
    for (int i = 1; i < m_parts.size(); i++)
        if (m_parts[0].getPosition().x == m_parts[i].getPosition().x &&
            m_parts[0].getPosition().y == m_parts[i].getPosition().y)
            return true;
    return false;
}

void Snake::update()
{
    if (appleInSnake())
    {
        sf::RectangleShape part;
        part.setPosition(m_apple.getPosition());
        part.setSize(sf::Vector2f(m_windowScale, m_windowScale));
        part.setFillColor(sf::Color::Green);
        m_parts.emplace_back(part);
        deployApple();
    }
}

bool Snake::gameOver()
{
    return m_parts[0].getPosition().x < 0 ||
           m_parts[0].getPosition().y < 0 ||
           m_parts[0].getPosition().x == m_windowWidth * m_windowScale ||
           m_parts[0].getPosition().y == m_windowHeight * m_windowScale ||
           headInSnake();
}
