#include "FpsCounter.hpp"

FpsCounter::FpsCounter(sf::Vector2f position, sf::Color color) :
m_clock(),
m_text(),
m_font()
{
    if (!m_font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setPosition(position);
    m_text.setFillColor(color);
}

void FpsCounter::update()
{
    std::stringstream ss;
    ss << std::trunc(1 / m_clock.restart().asSeconds());
    m_text.setString(ss.str());
}

void FpsCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(m_text, states);
}
