#include <iostream>
#include <cmath>
#include "constants.hpp"
#include <SFML/Graphics.hpp>

typedef struct spring_s
{
    int spring1, spring2;
    float length;
    float nx, ny;
} Spring;

typedef struct point_s
{
    float x, y;
    float fx, fy;
    float vx, vy;
} Point;

std::vector<Point> myPoints(NUM_POINTS);
std::vector<Spring> mySprings(NUM_SPRINGS);
float pressure;
bool mousePressed = false;

/* Define setup functions */
void addSpring(int i, int j, int k)
{
    mySprings[i].spring1 = j;
    mySprings[i].spring2 = k;
    mySprings[i].length = sqrtf(  // TODO: Square instead of multiplying (pow?)
            (myPoints[j].x - myPoints[k].x) * (myPoints[j].x - myPoints[k].x) +
            (myPoints[j].y - myPoints[k].y) * (myPoints[j].y - myPoints[k].y)
    );
}

void createBall()
{
    for (int i = 0; i < NUM_POINTS; i++)  // TODO: Fix types of constants
    {
        myPoints[i].x = BALL_RADIUS * (float)cos(i * 2 * PI / NUM_POINTS) + WIDTH / 2;
        myPoints[i].y = BALL_RADIUS * (float)sin(i * 2 * PI / NUM_POINTS) + HEIGHT / 4;
    }
    for (int i = 0; i < NUM_POINTS - 1; i++)
    {
        addSpring(i, i, i + 1);
    }
    addSpring(NUM_POINTS - 1, NUM_POINTS - 1, 0);
}

/* Define functions used to calculate force */
void accumulateForces()
{
    float x1, x2, y1, y2;
	float r12d;
	float vx12;
	float vy12;
	float f;
	float fx0, fy0;
	float volume = 0;
	float pressurev;

    for (int i = 0; i < NUM_POINTS; i++)
    {
        myPoints[i].fx = 0;
        myPoints[i].fy = (pressure - FINAL_PRESSURE) >= 0 ? GY * MASS : 0;
    }

    if (mousePressed)
    {
        x1 = myPoints[0].x;
        y1 = myPoints[0].y;
        x2 = sf::Mouse::getPosition().x;
        y2 = sf::Mouse::getPosition().y;

        r12d = (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        f = (float)(r12d - 2.2) * 22 + (myPoints[0].vx * (x1 - x2) + myPoints[0].vy * (y1 - y2)) * 54 / r12d;

        fx0 = ((x1 - x2) / r12d ) * f;
        fy0 = ((y1 - y2) / r12d ) * f;

        myPoints[0].fx -= fx0;
        myPoints[0].fy -= fy0;
	}

    for (int i = 0; i < NUM_SPRINGS; i++)
    {
		x1 = myPoints[mySprings[i].spring1].x;
		x2 = myPoints[mySprings[i].spring2].x;
		y1 = myPoints[mySprings[i].spring1].y;
		y2 = myPoints[mySprings[i].spring2].y;

		// Find the distance between each spring
		r12d = sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

		// Accumulate spring forces
		if (r12d != 0)
        {
			vx12 = myPoints[mySprings[i].spring1].vx - myPoints[mySprings[i].spring2].vx;
			vy12 = myPoints[mySprings[i].spring1].vy - myPoints[mySprings[i].spring2].vy;

			f = (r12d - mySprings[i].length) * KS + (vx12 * (x1 - x2) + vy12 * (y1 - y2)) * KD / r12d;

			fx0 = ((x1 - x2) / r12d ) * f;
			fy0 = ((y1 - y2) / r12d ) * f;

			myPoints[mySprings[i].spring1].fx -= fx0;
			myPoints[mySprings[i].spring1].fy -= fy0;

			myPoints[mySprings[i].spring2].fx += fx0;
			myPoints[mySprings[i].spring2].fy += fy0;
		}
		// Calculate normal vectors for use with finding pressure force
		mySprings[i].nx = -(y1 - y2) / r12d;
		mySprings[i].ny = (x1 - x2) / r12d;
	}

    for (int i = 0; i < NUM_SPRINGS; i++)
    {
		x1 = myPoints[mySprings[i].spring1].x;
		x2 = myPoints[mySprings[i].spring2].x;
		y1 = myPoints[mySprings[i].spring1].y;
		y2 = myPoints[mySprings[i].spring2].y;

		r12d = sqrtf((x1 - x2) *(x1 - x2)  +  (y1 - y2) * (y1 - y2));

		volume += 0.5 * abs(x1 - x2) * abs(mySprings[i].nx) * (r12d);
	}

	for (int i = 0; i < NUM_SPRINGS; i++)
    {
		x1 = myPoints[mySprings[i].spring1].x;
		x2 = myPoints[mySprings[i].spring2].x;
		y1 = myPoints[mySprings[i].spring1].y;
		y2 = myPoints[mySprings[i].spring2].y;

		r12d = sqrtf((x1 - x2) * (x1 - x2)  +  (y1 - y2) * (y1 - y2));

		pressurev = r12d * pressure * (1.0 / volume);

		myPoints[mySprings[i].spring1].fx += mySprings[i].nx * pressurev;
		myPoints[mySprings[i].spring1].fy += mySprings[i].ny *pressurev;
		myPoints[mySprings[i].spring2].fx += mySprings[i].nx *pressurev;
		myPoints[mySprings[i].spring2].fy += mySprings[i].ny *pressurev;
	}
}

void integrateHeun()
{
	float drx, dry;
	std::vector<float> fxsaved(NUM_POINTS);
	std::vector<float> fysaved(NUM_POINTS);
	std::vector<float> vxsaved(NUM_POINTS);
	std::vector<float> vysaved(NUM_POINTS);

	for (int i = 0; i < NUM_POINTS; i++)
    {
		fxsaved[i] = myPoints[i].fx;
		fysaved[i] = myPoints[i].fy;

		vxsaved[i] = myPoints[i].vx;
		vysaved[i] = myPoints[i].vy;

		myPoints[i].vx += myPoints[i].fx / MASS * DT;
		drx = myPoints[i].vx * DT;

		myPoints[i].x += drx;

		myPoints[i].vy += myPoints[i].fy / MASS * DT;
		dry = myPoints[i].vy * DT;

		myPoints[i].y += dry;
	}

	accumulateForces();

	for (int i=0; i<NUM_POINTS; i++)
    {
		myPoints[i].vx = vxsaved[i] + (myPoints[i].fx + fxsaved[i]) / MASS * DT / 2;
		drx = myPoints[i].vx * DT;

		myPoints[i].x += drx;

		myPoints[i].vy = vysaved[i] + (myPoints[i].fy + fysaved[i]) / MASS * DT / 2;
		dry = myPoints[i].vy * DT;

		myPoints[i].y += dry;
	}
}

void update()
{
    accumulateForces();
    integrateHeun();

    if (pressure < FINAL_PRESSURE)
		pressure += FINAL_PRESSURE / 300.;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Soft Body");
    createBall();
    sf::ConvexShape shape;
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                mousePressed = true;
            if (event.type == sf::Event::MouseButtonReleased)
                mousePressed = false;
        }

        for (int i = 0; i < NUM_POINTS; i++)
            shape.setPoint(i, sf::Vector2f(myPoints[i].x, myPoints[i].y));
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}