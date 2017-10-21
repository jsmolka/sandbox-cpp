#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    sf::Window window(sf::VideoMode(800, 600), "Event window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::Resized:
                    cout << "New width: " << window.getSize().x << endl;
                    cout << "New height: " << window.getSize().y << endl;
                    break;

                case sf::Event::KeyPressed:
                    cout << "Pressed key code: " << event.key.code << endl;
                    break;

                case sf::Event::TextEntered:
                    cout << "Pressed key: " << static_cast<char>(event.text.unicode) << endl;
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right)
                        cout << "The right mouse button was pressed" << endl;
                    else if (event.mouseButton.button == sf::Mouse::Left)
                        cout << "The left mouse button was pressed" << endl;

                    cout << "Mouse x: " << event.mouseButton.x << endl;
                    cout << "Mouse y: " << event.mouseButton.y << endl;
                    break;

                case sf::Event::MouseMoved:
                    cout << "Mouse x: " << event.mouseMove.x << endl;
                    cout << "Mouse y: " << event.mouseMove.y << endl;
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}