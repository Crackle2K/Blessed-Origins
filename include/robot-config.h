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

// Drive configuration
extern const double DRIVE_DEADZONE;
extern const double DRIVE_SENSITIVITY;

// Function declarations
void configureRobot();

#endif
