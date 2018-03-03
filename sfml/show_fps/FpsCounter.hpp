#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class FpsCounter : public sf::Drawable, public sf::Transformable
{
public:
    FpsCounter(sf::Vector2f position, unsigned int fps, unsigned int size, sf::Color color, std::string fontPath) :
    mClock(),
    mText(),
    mFont(),
    mFrame(0),
    mFps(1.f / fps),
    mTotal(0)
    {
        if (!mFont.loadFromFile(fontPath))
        {
            std::cerr << "Could not load font: " << fontPath << std::endl;
        }
        mText.setFont(mFont);
        mText.setPosition(position);
        mText.setFillColor(color);
        mText.setCharacterSize(size);
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
        mFrame++;
        mTotal += mClock.restart().asSeconds();
        if (mTotal >= mFps)
        {
            mText.setString(std::to_string(static_cast<int>(mFrame / mTotal)));
            mTotal = mFrame = 0;
        }
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        states.texture = nullptr;
        target.draw(mText, states);
    }

    sf::Clock mClock;
    sf::Text mText;
    sf::Font mFont;
    unsigned int mFrame;
    float mFps;
    float mTotal;
};

#endif //FPS_COUNTER_HPP
