#include <algorithm>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constants.hpp"

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
float mouseX;
float mouseY;

/* Define setup functions */
void addSpring(int i, int j, int k)
{
    mySprings[i].spring1 = j;
    mySprings[i].spring2 = k;
    mySprings[i].length = sqrtf(
        powf(myPoints[j].x - myPoints[k].x, 2) +
        powf(myPoints[j].y - myPoints[k].y, 2)
    );
}

void createBall()
{
    for (int i = 0; i < NUM_POINTS; i++)
    {
        myPoints[i].x = BALL_RADIUS * cosf(i * 2 * PI / NUM_POINTS) + WIDTH / 2;
        myPoints[i].y = BALL_RADIUS * sinf(i * 2 * PI / NUM_POINTS) + HEIGHT / 4;
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
        x2 = mouseX;
        y2 = mouseY;

        r12d = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
        f = (r12d - 2.2f) * 22 + (myPoints[0].vx * (x1 - x2) + myPoints[0].vy * (y1 - y2)) * 54 / r12d;

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

		volume += 0.5 * fabsf(x1 - x2) * fabsf(mySprings[i].nx) * (r12d);
	}

	for (int i = 0; i < NUM_SPRINGS; i++)
    {
		x1 = myPoints[mySprings[i].spring1].x;
		x2 = myPoints[mySprings[i].spring2].x;
		y1 = myPoints[mySprings[i].spring1].y;
		y2 = myPoints[mySprings[i].spring2].y;

		r12d = sqrtf((x1 - x2) * (x1 - x2)  +  (y1 - y2) * (y1 - y2));

		pressurev = r12d * pressure * (1.f / volume);

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
		myPoints[i].vy += myPoints[i].fy / MASS * DT;

        drx = myPoints[i].vx * DT;
        dry = myPoints[i].vy * DT;

		myPoints[i].x += drx;
		myPoints[i].y += dry;
    }

    accumulateForces();

    for (int i = 0; i < NUM_POINTS; i++)
    {
		myPoints[i].vx = vxsaved[i] + (myPoints[i].fx + fxsaved[i]) / MASS * DT / 2;
        myPoints[i].vy = vysaved[i] + (myPoints[i].fy + fysaved[i]) / MASS * DT / 2;

        drx = myPoints[i].vx * DT;
        dry = myPoints[i].vy * DT;

		myPoints[i].x += drx;
		myPoints[i].y += dry;

        // Boundary checking
        myPoints[i].x = std::min(myPoints[i].x, WIDTH/2.f + RADIUS);
		myPoints[i].x = std::max(myPoints[i].x, WIDTH/2.f - RADIUS);

		myPoints[i].y = std::min(myPoints[i].y, HEIGHT/2.f + RADIUS);
		myPoints[i].y = std::max(myPoints[i].y, HEIGHT/2.f - RADIUS);

		if (myPoints[i].x + drx >  sqrtf(R2 - powf(myPoints[i].y - HEIGHT / 2.f, 2)) + WIDTH / 2. ||
			myPoints[i].x + drx < -sqrtf(R2 - powf(myPoints[i].y - HEIGHT / 2.f, 2)) + WIDTH / 2.)
		{
			float vx0 = myPoints[i].vx;
			float vy0 = myPoints[i].vy;

			float sinTheta = (myPoints[i].y - HEIGHT / 2.f) / RADIUS;
			float cosTheta = (myPoints[i].x - WIDTH / 2.f) / RADIUS;

			myPoints[i].vx = -vx0;
			myPoints[i].vy = -vy0;
			myPoints[i].vx = vy0 * (-TDF * sinTheta * cosTheta - NDF * sinTheta * cosTheta) + vx0 * (TDF * sinTheta * sinTheta - NDF * cosTheta * cosTheta);
			myPoints[i].vy = vy0 * (TDF * cosTheta * cosTheta - NDF * sinTheta * sinTheta) + vx0 * (-TDF * sinTheta * cosTheta - NDF * sinTheta * cosTheta);
		}

		if (myPoints[i].y > HEIGHT / 2.f + RADIUS / 2.f)
			myPoints[i].y = std::min(myPoints[i].y,  sqrtf(fabsf(R2 - powf(myPoints[i].x - WIDTH / 2.f, 2))) + HEIGHT / 2.f);

		if (myPoints[i].y < HEIGHT / 2.f - RADIUS / 2.f)
            myPoints[i].y = std::max(myPoints[i].y, -sqrtf(fabsf(R2 - powf(myPoints[i].x - WIDTH / 2.f, 2))) + HEIGHT / 2.f);

		if (myPoints[i].x > WIDTH / 2.f + RADIUS / 2.f)
			myPoints[i].x = std::min(myPoints[i].x,  sqrtf(fabsf(R2 - powf(myPoints[i].y - HEIGHT / 2.f, 2))) + WIDTH / 2.f);

		if (myPoints[i].x < WIDTH / 2.f - RADIUS / 2.f)
			myPoints[i].x = std::max(myPoints[i].x, -sqrtf(fabsf(R2 - powf(myPoints[i].y - HEIGHT / 2.f, 2))) + WIDTH / 2.f);
	}
}

void update()
{
    accumulateForces();
    integrateHeun();

    if (pressure < FINAL_PRESSURE)
		pressure += FINAL_PRESSURE / 300.f;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Soft Body");
    window.setFramerateLimit(120);

    sf::ConvexShape shape(NUM_POINTS);
    shape.setFillColor(sf::Color::Red);

    sf::CircleShape circle;
    circle.setPointCount(200);
    circle.setRadius(RADIUS);
    circle.setPosition(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);

    createBall();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                mousePressed = true;
            if (event.type == sf::Event::MouseButtonReleased)
                mousePressed = false;
        }

        if (mousePressed)
        {
            mouseX = sf::Mouse::getPosition(window).x;
            mouseY = sf::Mouse::getPosition(window).y;
        }

        update();
        update();
        for (size_t i = 0; i < NUM_POINTS; i++)
            shape.setPoint(i, sf::Vector2f(myPoints[i].x, myPoints[i].y));

        window.clear();
        window.draw(circle);
        window.draw(shape);
        window.display();
    }
    return 0;
}
