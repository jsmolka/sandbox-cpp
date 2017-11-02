#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP

#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>

class FpsCounter : public sf::Drawable, public sf::Transformable
{
public:
    FpsCounter(sf::Vector2f position, sf::Color color);
    void update();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Clock m_clock;
    sf::Text m_text;
    sf::Font m_font;
};

#endif //FPS_COUNTER_HPP
