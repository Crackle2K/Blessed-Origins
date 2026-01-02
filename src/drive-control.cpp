#include "vex.h"
#include "drive-control.h"
#include <cmath>

using namespace vex;

// ========================================
// ClawDrive Class Implementation
// ========================================

ClawDrive::ClawDrive(motor& leftFront, motor& leftBack, motor& rightFront, motor& rightBack,
                     double deadzone, double sensitivity)
  : m_leftFront(leftFront),
    m_leftBack(leftBack),
    m_rightFront(rightFront),
    m_rightBack(rightBack),
    m_deadzone(deadzone),
    m_sensitivity(sensitivity) {
  // Constructor - motors are now initialized
}

void ClawDrive::setDeadzone(double deadzone) {
  m_deadzone = deadzone;
}

void ClawDrive::setSensitivity(double sensitivity) {
  m_sensitivity = sensitivity;
}

double ClawDrive::getDeadzone() const {
  return m_deadzone;
}

double ClawDrive::getSensitivity() const {
  return m_sensitivity;
}

/**
 * Apply deadzone to controller input
 */
double ClawDrive::applyDeadzone(double value) const {
  if (fabs(value) < m_deadzone) {
    return 0.0;
  }
  return value;
}

/**
 * Clamp value to range
 */
double ClawDrive::clamp(double value, double min, double max) const {
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
void ClawDrive::arcadeDrive(double forward, double turn) {
  // Apply deadzone to prevent controller drift
  forward = applyDeadzone(forward);
  turn = applyDeadzone(turn);
  
  // Apply sensitivity
  forward *= m_sensitivity;
  turn *= m_sensitivity;
  
  // Calculate left and right motor velocities
  // This formula combines forward and turning motion for smooth diagonal movement
  double leftVelocity = forward + turn;
  double rightVelocity = forward - turn;
  
  // Clamp velocities to valid range (-100 to 100)
  leftVelocity = clamp(leftVelocity, -100.0, 100.0);
  rightVelocity = clamp(rightVelocity, -100.0, 100.0);
  
  // Set motor velocities
  m_leftFront.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  m_leftBack.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  m_rightFront.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
  m_rightBack.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
}

/**
 * Tank drive with individual side control
 * 
 * Allows independent control of left and right sides.
 * Diagonal movement is achieved by setting different velocities
 * for each side (e.g., left at 50%, right at 75% for diagonal-right).
 */
void ClawDrive::tankDrive(double left, double right) {
  // Apply deadzone
  left = applyDeadzone(left);
  right = applyDeadzone(right);
  
  // Apply sensitivity
  left *= m_sensitivity;
  right *= m_sensitivity;
  
  // Clamp velocities
  left = clamp(left, -100.0, 100.0);
  right = clamp(right, -100.0, 100.0);
  
  // Set motor velocities
  m_leftFront.spin(directionType::fwd, left, velocityUnits::pct);
  m_leftBack.spin(directionType::fwd, left, velocityUnits::pct);
  m_rightFront.spin(directionType::fwd, right, velocityUnits::pct);
  m_rightBack.spin(directionType::fwd, right, velocityUnits::pct);
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
void ClawDrive::fieldCentricDrive(double forward, double strafe, double turn) {
  // Apply deadzone to all inputs
  forward = applyDeadzone(forward);
  strafe = applyDeadzone(strafe);
  turn = applyDeadzone(turn);
  
  // Apply sensitivity
  forward *= m_sensitivity;
  strafe *= m_sensitivity;
  turn *= m_sensitivity;
  
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
  m_leftFront.spin(directionType::fwd, leftFrontVelocity, velocityUnits::pct);
  m_leftBack.spin(directionType::fwd, leftBackVelocity, velocityUnits::pct);
  m_rightFront.spin(directionType::fwd, rightFrontVelocity, velocityUnits::pct);
  m_rightBack.spin(directionType::fwd, rightBackVelocity, velocityUnits::pct);
}

/**
 * Stop all drive motors
 */
void ClawDrive::stop() {
  m_leftFront.stop();
  m_leftBack.stop();
  m_rightFront.stop();
  m_rightBack.stop();
}
