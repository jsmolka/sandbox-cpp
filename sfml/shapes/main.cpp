#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Use anti aliasing for render window

    sf::RenderWindow window(sf::VideoMode(800, 600), "Render window", sf::Style::Default, settings);
    window.setFramerateLimit(5);  // Set frame rate for easier spectating
    unsigned int frame = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frame++;

        // Clear window with black background color
        window.clear(sf::Color::Black);

        // Basic shapes
        sf::CircleShape circle(50);
        circle.setRadius(50);
        circle.setPointCount(100);

        sf::RectangleShape rectangle(sf::Vector2f(100, 50));
        rectangle.setSize(sf::Vector2f(100, 50));

        // Regular polygons
        sf::CircleShape triangle(50, 3);
        sf::CircleShape square(50, 4);
        sf::CircleShape octagon(50, 8);
        sf::CircleShape polygon(200, frame);
        polygon.setPosition(200, 100);

        // Convex shapes
        sf::ConvexShape convex(5);
        convex.setPoint(0, sf::Vector2f(10, 10));
        convex.setPoint(1, sf::Vector2f(200, 10));
        convex.setPoint(2, sf::Vector2f(100, 100));
        convex.setPoint(3, sf::Vector2f(200, 200));
        convex.setPoint(4, sf::Vector2f(10, 200));

        // Lines
        // Line with thickness is a rectangle
        // Line without thickness can be drawn as a primitive
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(800, 600)),
            sf::Vertex(sf::Vector2f(700, 500))
        };
        
        // Draw shapes
        window.draw(polygon);
        window.draw(convex);
        window.draw(line, 2, sf::Lines);

        // Draw current window frame
        window.display();
    }

    return 0;
}