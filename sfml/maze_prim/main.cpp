#include <iostream>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

const unsigned int SCALE = 5;
const unsigned int ROW_COUNT = 60;
const unsigned int COL_COUNT = 60;
const unsigned int ROW_COUNT_WITH_WALLS = 2 * ROW_COUNT + 1;
const unsigned int COL_COUNT_WITH_WALLS = 2 * COL_COUNT + 1;
const unsigned int BLACK = 0;
const unsigned int MARKED = 1;
const unsigned int WHITE = 2;
vector<sf::Vector2f> draw;
vector<vector<unsigned int>> maze;
vector<sf::Vector2f> frontier;

// Define directions
sf::Vector2f n1(sf::Vector2f vector) {vector.y -= 1; return vector;}
sf::Vector2f s1(sf::Vector2f vector) {vector.y += 1; return vector;}
sf::Vector2f e1(sf::Vector2f vector) {vector.x += 1; return vector;}
sf::Vector2f w1(sf::Vector2f vector) {vector.x -= 1; return vector;}
sf::Vector2f n2(sf::Vector2f vector) {vector.y -= 2; return vector;}
sf::Vector2f s2(sf::Vector2f vector) {vector.y += 2; return vector;}
sf::Vector2f e2(sf::Vector2f vector) {vector.x += 2; return vector;}
sf::Vector2f w2(sf::Vector2f vector) {vector.x -= 2; return vector;}

typedef sf::Vector2f (*Direction) (sf::Vector2f vector);
Direction dir_one[] = {n1, s1, e1, w1};
Direction dir_two[] = {n2, s2, e2, w2};

template <typename T>
T pop_random(std::vector<T>& v)
{
    std::swap(v[rand() % v.size()], v.back());
    T value = v[v.size() - 1];
    v.pop_back();
    return value;
}

bool out_of_bounds(sf::Vector2f vector)
{
    return vector.x < 0 || vector.y < 0 || vector.x >= ROW_COUNT_WITH_WALLS || vector.y >= COL_COUNT_WITH_WALLS;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCALE * COL_COUNT_WITH_WALLS, SCALE * ROW_COUNT_WITH_WALLS), "Maze Prim");
    maze.resize(COL_COUNT_WITH_WALLS, vector<unsigned int>(ROW_COUNT_WITH_WALLS, BLACK));
    srand(static_cast<unsigned int>(time(NULL)));

    // Get initial coordinates
    sf::Vector2f first;
    first.x = 2 * (rand() % ROW_COUNT) + 1;
    first.y = 2 * (rand() % COL_COUNT) + 1;
    maze[first.x][first.y] = WHITE;
    draw.emplace_back(first);

    // Generate frontier for initial coordinates
    for (auto &func : dir_two) {
        sf::Vector2f cell = func(first);
        if (!out_of_bounds(cell))
        {
            maze[cell.x][cell.y] = MARKED;
            frontier.emplace_back(cell);
        }
    }

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

         window.clear();

        if (!frontier.empty())
        {
            // Mark random cell of frontier as visited
            sf::Vector2f cell = pop_random(frontier);
            for (int i = 0; i < 4; i++)
            {
                sf::Vector2f test = dir_two[i](cell);  // TODO: shuffle dir two
                if (!out_of_bounds(test) && maze[test.x][test.y] == WHITE)
                {
                    sf::Vector2f between = dir_one[i](cell);
                    maze[cell.x][cell.y] = maze[between.x][between.y] = WHITE;
                    draw.emplace_back(cell);
                    draw.emplace_back(between);
                    break;
                }
            }

            // Find adjacent cells of popped cell
            for (auto &func : dir_two)
            {
                sf::Vector2f test = func(cell);
                if (!out_of_bounds(test) && maze[test.x][test.y] == BLACK)
                {
                    frontier.emplace_back(test);
                    maze[test.x][test.y] = MARKED;
                }
            }
        }

        // Draw maze
        for (auto &cell : draw) {
            sf::RectangleShape rect;
            rect.setPosition(cell.x * SCALE, cell.y * SCALE);
            rect.setFillColor(sf::Color::White);
            rect.setSize(sf::Vector2f(SCALE, SCALE));
            window.draw(rect);
        }
        window.display();
    }
    return 0;
}