#include "vex.h"
#include "robot-config.h"
#include "drive-control.h"
#include <cmath>

using namespace vex;

/**
 * Apply deadzone to controller input
 */
double applyDeadzone(double value, double deadzone) {
  if (fabs(value) < deadzone) {
    return 0.0;
  }
  return value;
}

/**
 * Clamp value to range
 */
double clamp(double value, double min, double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

/**
 * Dual-stick arcade drive with smooth diagonal movement
 * 
 * This is the recommended control scheme for smooth diagonal movement.
 * The forward and turn inputs are combined using vector addition,
 * allowing the robot to move diagonally when both inputs are active.
 * 
 * For example:
 * - Forward only: Robot moves straight forward
 * - Turn only: Robot rotates in place
 * - Forward + Turn: Robot moves forward while turning (smooth arc/diagonal)
 */
void arcadeDrive(double forward, double turn) {
  // Apply deadzone to prevent controller drift
  forward = applyDeadzone(forward, DRIVE_DEADZONE);
  turn = applyDeadzone(turn, DRIVE_DEADZONE);
  
  // Apply sensitivity
  forward *= DRIVE_SENSITIVITY;
  turn *= DRIVE_SENSITIVITY;
  
  // Calculate left and right motor velocities
  // This formula combines forward and turning motion for smooth diagonal movement
  double leftVelocity = forward + turn;
  double rightVelocity = forward - turn;
  
  // Clamp velocities to valid range (-100 to 100)
  leftVelocity = clamp(leftVelocity, -100.0, 100.0);
  rightVelocity = clamp(rightVelocity, -100.0, 100.0);
  
  // Set motor velocities
  LeftFront.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  RightFront.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
  RightBack.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
}

/**
 * Tank drive with individual side control
 * 
 * Allows independent control of left and right sides.
 * Diagonal movement is achieved by setting different velocities
 * for each side (e.g., left at 50%, right at 75% for diagonal-right).
 */
void tankDrive(double left, double right) {
  // Apply deadzone
  left = applyDeadzone(left, DRIVE_DEADZONE);
  right = applyDeadzone(right, DRIVE_DEADZONE);
  
  // Apply sensitivity
  left *= DRIVE_SENSITIVITY;
  right *= DRIVE_SENSITIVITY;
  
  // Clamp velocities
  left = clamp(left, -100.0, 100.0);
  right = clamp(right, -100.0, 100.0);
  
  // Set motor velocities
  LeftFront.spin(directionType::fwd, left, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, left, velocityUnits::pct);
  RightFront.spin(directionType::fwd, right, velocityUnits::pct);
  RightBack.spin(directionType::fwd, right, velocityUnits::pct);
}

/**
 * Field-centric drive for omnidirectional movement
 * 
 * This control scheme is designed for mecanum wheels or X-drive configurations.
 * It enables true diagonal movement where the robot can move in any direction
 * while independently controlling rotation.
 * 
 * The motor velocities are calculated using vector addition:
 * - Forward/backward component affects all wheels equally
 * - Strafe component creates diagonal movement by opposing front/back wheels
 * - Turn component rotates the robot
 * 
 * Note: For standard tank drive robots, use arcadeDrive instead.
 */
void fieldCentricDrive(double forward, double strafe, double turn) {
  // Apply deadzone to all inputs
  forward = applyDeadzone(forward, DRIVE_DEADZONE);
  strafe = applyDeadzone(strafe, DRIVE_DEADZONE);
  turn = applyDeadzone(turn, DRIVE_DEADZONE);
  
  // Apply sensitivity
  forward *= DRIVE_SENSITIVITY;
  strafe *= DRIVE_SENSITIVITY;
  turn *= DRIVE_SENSITIVITY;
  
  // Calculate motor velocities for mecanum/X-drive
  // This formula enables true omnidirectional movement
  double leftFrontVelocity = forward + strafe + turn;
  double leftBackVelocity = forward - strafe + turn;
  double rightFrontVelocity = forward - strafe - turn;
  double rightBackVelocity = forward + strafe - turn;
  
  // Find the maximum absolute velocity to scale if needed
  double maxLeft = fmax(fabs(leftFrontVelocity), fabs(leftBackVelocity));
  double maxRight = fmax(fabs(rightFrontVelocity), fabs(rightBackVelocity));
  double maxVelocity = fmax(maxLeft, maxRight);
  
  // Scale down if any velocity exceeds 100%
  if (maxVelocity > 100.0) {
    leftFrontVelocity = (leftFrontVelocity / maxVelocity) * 100.0;
    leftBackVelocity = (leftBackVelocity / maxVelocity) * 100.0;
    rightFrontVelocity = (rightFrontVelocity / maxVelocity) * 100.0;
    rightBackVelocity = (rightBackVelocity / maxVelocity) * 100.0;
  }
  
  // Set motor velocities
  LeftFront.spin(directionType::fwd, leftFrontVelocity, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, leftBackVelocity, velocityUnits::pct);
  RightFront.spin(directionType::fwd, rightFrontVelocity, velocityUnits::pct);
  RightBack.spin(directionType::fwd, rightBackVelocity, velocityUnits::pct);
}
