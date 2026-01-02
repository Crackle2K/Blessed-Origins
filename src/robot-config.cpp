#include "vex.h"
#include "robot-config.h"

using namespace vex;

// VEX V5 Brain and Controller
brain Brain;
controller Controller1 = controller(primary);

// Drive Motors Configuration
// Adjust port numbers based on your robot's wiring
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

/**
 * Configure robot hardware and settings
 */
void configureRobot() {
  // Set motor brake modes for better control
  LeftFront.setStopping(brake);
  LeftBack.setStopping(brake);
  RightFront.setStopping(brake);
  RightBack.setStopping(brake);
  
  // Set motor velocity units
  LeftFront.setVelocity(0, percent);
  LeftBack.setVelocity(0, percent);
  RightFront.setVelocity(0, percent);
  RightBack.setVelocity(0, percent);
}
