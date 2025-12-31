#ifndef DRIVE_CONTROL_H
#define DRIVE_CONTROL_H

#include "vex.h"

using namespace vex;

/**
 * Drive Control System for VEX Robots
 * 
 * This module provides smooth diagonal movement capabilities using
 * dual-joystick arcade drive control. The system calculates proper
 * velocity vectors for each motor to enable precise diagonal movement.
 */

// ========================================
// Primary Drive Control Functions
// ========================================

/**
 * Dual-stick arcade drive with diagonal movement support
 * 
 * Left Stick Y-axis: Forward/Backward movement
 * Right Stick X-axis: Left/Right turning
 * 
 * When both inputs are active, the robot moves diagonally with smooth
 * interpolation between forward/back and turning motions.
 * 
 * @param forward Forward/backward velocity (-100 to 100)
 * @param turn Left/right turning velocity (-100 to 100)
 */
void arcadeDrive(double forward, double turn);

/**
 * Tank drive with individual side control for diagonal movement
 * 
 * Left Stick Y-axis: Left side motors
 * Right Stick Y-axis: Right side motors
 * 
 * Allows independent control of each side, enabling diagonal movement
 * by setting different velocities for left and right sides.
 * 
 * @param left Left side velocity (-100 to 100)
 * @param right Right side velocity (-100 to 100)
 */
void tankDrive(double left, double right);

/**
 * Field-centric drive for advanced diagonal movement
 * 
 * Provides true omnidirectional control where the robot can move
 * in any direction while independently controlling rotation.
 * 
 * Note: Requires mecanum wheels or X-drive configuration
 * 
 * @param forward Forward/backward velocity (-100 to 100)
 * @param strafe Left/right strafe velocity (-100 to 100)
 * @param turn Rotation velocity (-100 to 100)
 */
void fieldCentricDrive(double forward, double strafe, double turn);

// ========================================
// Utility Functions
// ========================================
// These are public to allow users to create custom drive functions
// or apply the same processing to other control inputs

/**
 * Apply deadzone to controller input
 * 
 * Eliminates controller drift by ignoring small values near zero.
 * 
 * @param value Controller axis value
 * @param deadzone Minimum threshold for input
 * @return Processed value (0 if within deadzone)
 */
double applyDeadzone(double value, double deadzone);

/**
 * Clamp value to range
 * 
 * @param value Input value
 * @param min Minimum value
 * @param max Maximum value
 * @return Clamped value
 */
double clamp(double value, double min, double max);

#endif
