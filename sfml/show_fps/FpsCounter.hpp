#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class FpsCounter : public sf::Drawable, public sf::Transformable
{
public:
    FpsCounter(sf::Vector2f position, unsigned int fps, unsigned int size, sf::Color color, std::string fontPath) :
    m_clock(),
    m_text(),
    m_font(),
    m_frame(0),
    m_fps(1.f / fps),
    m_total(0)
    {
        if (!m_font.loadFromFile(fontPath))
        {
            std::cerr << "Could not load font: " << fontPath << std::endl;
        }
        m_text.setFont(m_font);
        m_text.setPosition(position);
        m_text.setFillColor(color);
        m_text.setCharacterSize(size);
    }

    FpsCounter(sf::Vector2f position, unsigned int fps, unsigned int size, sf::Color color) :
    FpsCounter(position, fps, size, color, "Arial.ttf")
    {
    }

    FpsCounter(sf::Vector2f position, unsigned int fps, unsigned int size) :
    FpsCounter(position, fps, size, sf::Color::White)
    {
    }

    FpsCounter(sf::Vector2f position, unsigned int fps) :
    FpsCounter(position, fps, 20)
    {
    }

    explicit FpsCounter(sf::Vector2f position) :
    FpsCounter(position, 10)
    {
    }

    void update()
    {
        m_frame++;
        m_total += m_clock.restart().asSeconds();
        if (m_total >= m_fps)
        {
            m_text.setString(std::to_string(static_cast<int>(m_frame / m_total)));
            m_total = m_frame = 0;
        }
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        states.texture = nullptr;
        target.draw(m_text, states);
    }

    sf::Clock m_clock;
    sf::Text m_text;
    sf::Font m_font;
    unsigned int m_frame;
    float m_fps;
    float m_total;
};

#endif //FPS_COUNTER_HPP
