#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "vex.h"

using namespace vex;

// VEX V5 Brain and Controller
extern brain Brain;
extern controller Controller1;

// Drive Motors
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;

// Function declarations
void configureRobot();

#endif
