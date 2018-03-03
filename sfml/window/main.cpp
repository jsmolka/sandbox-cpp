#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window", sf::Style::Default);
    /* Third argument for the constructor can be a style enum (not necessary)
     * sf::Style::None          no decoration
     * sf::Style::Titlebar      window with titlebar
     * sf::Style::Resize        resizeable window with maximize button
     * sf::Style::Close         window has a close button
     * sf::Style::Fullscreen    window is shown in fullscreen mode
     * sf::Style::Default       default style with titlebar, resize, close
    */
    // Test some window settings
    cout << "Window position: " << window.getPosition().x << ", " << window.getPosition().y << endl;
    cout << "Window size: " << window.getSize().x << ", " << window.getSize().y << endl;
    cout << "Window focus: " << window.hasFocus() << endl;
    cout << "Window open: " << window.isOpen() << endl;
    // Some functions
    window.setActive();
    window.setFramerateLimit(60);  // Not 100% reliable because of sf::Clock and sf::sleep
    window.setVerticalSyncEnabled(true);  // No effect is vsync is forced to be disabled in gpu driver
    window.setTitle("Still my window");
    window.close();

    // Recreate window
    int count = 0;
    window.create(sf::VideoMode(800, 600), "Yet another window");
    while (window.isOpen())  // Keep window open
    {
        count++;
        cout << "Current frame: " << count << endl;

        sf::Event event;  // Get all triggered events since the last loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();  // Close window at close request
        }
    }

    return 0;
}