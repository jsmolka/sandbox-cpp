#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Render window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Use the predefined VertexArray class
        sf::VertexArray triangle(sf::Triangles, 3);
        triangle[0].position = sf::Vector2f(10, 10);
        triangle[1].position = sf::Vector2f(790, 10);
        triangle[2].position = sf::Vector2f(10, 590);

        triangle[0].color = sf::Color::Red;
        triangle[1].color = sf::Color::Green;
        triangle[2].color = sf::Color::Blue;

        // Use the stdlib vector template
        std::vector<sf::Vertex> triangle2;
        triangle2.emplace_back(sf::Vertex(sf::Vector2f(790, 10), sf::Color::Green));
        triangle2.emplace_back(sf::Vertex(sf::Vector2f(790, 590), sf::Color::Red));
        triangle2.emplace_back(sf::Vertex(sf::Vector2f(10, 590), sf::Color::Blue));

        /* Available primitive types
         * Points
         * Lines
         * LineStrip
         * Triangles
         * TriangleStrip
         * TriangleFan
         * Quads */

        // Draw vertex arrays
        window.draw(triangle);
        window.draw(&triangle2[0], triangle2.size(), sf::Triangles);

        window.display();
    }

    return 0;
}