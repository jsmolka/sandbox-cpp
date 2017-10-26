#ifndef SOFT_BODY_CONSTANTS_HPP
#define SOFT_BODY_CONSTANTS_HPP

#include <cmath>

int FPS              = 120;
int NUM_POINTS       = 20;  // Default: 20
int NUM_SPRINGS      = NUM_POINTS;
int LENGTH           = 75;
int WIDTH            = 1200;
int HEIGHT           = 500;
float RADIUS         = 190.0;
float R2             = (float)pow(RADIUS, 2);
// Ball constants
float MASS           = 1.0;
float BALL_RADIUS    = 0.516;  // Default: 0.516
// Spring constants
float KS             = 755.0;  // Default: 755
float KD             = 35.0;  // Default: 35.0
// Gravity force and user applied force
float GY             = 110.0;  // Default: 110.0
float FAPP           = 110.0;
// Time interval for numeric integration
float DT             = 0.01;  // Default: 0.005
float FINAL_PRESSURE = 70000;  //Default: 70000
// Tangential and normal damping factors
float TDF            = 0.99;  // Default: 0.95 by default
// A TDF of 1.0 means frictionless boundaries.
// If some energy were not lost due to the ball's
// spring-damping, the ball could continue
// traveling forever without any force.
float NDF            = 0.1;  // Default: 0.1

#endif //SOFT_BODY_CONSTANTS_HPP
