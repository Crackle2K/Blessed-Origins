#ifndef DRIVE_CONTROL_H
#define DRIVE_CONTROL_H

#include "vex.h"

using namespace vex;

/**
 * Claw Drive Control Library for VEX V5 Robots
 * 
 * This library provides smooth diagonal movement capabilities for VEX V5 robots.
 * It supports multiple drive control methods including arcade, tank, and field-centric.
 * 
 * Usage:
 *   1. Create a ClawDrive instance with your motors
 *   2. Call drive control methods (arcadeDrive, tankDrive, etc.)
 *   3. Optionally configure sensitivity and deadzone
 */

// ========================================
// ClawDrive Library Class
// ========================================

class ClawDrive {
private:
  // Motor references
  motor& m_leftFront;
  motor& m_leftBack;
  motor& m_rightFront;
  motor& m_rightBack;
  
  // Configuration
  double m_deadzone;
  double m_sensitivity;
  
  // Utility functions
  double applyDeadzone(double value) const;
  double clamp(double value, double min, double max) const;

public:
  /**
   * Constructor: Initialize ClawDrive with motor references
   * 
   * @param leftFront Left front motor
   * @param leftBack Left back motor
   * @param rightFront Right front motor
   * @param rightBack Right back motor
   * @param deadzone Controller deadzone percentage (default: 5.0)
   * @param sensitivity Drive sensitivity multiplier (default: 1.0)
   */
  ClawDrive(motor& leftFront, motor& leftBack, motor& rightFront, motor& rightBack,
            double deadzone = 5.0, double sensitivity = 1.0);
  
  /**
   * Set controller deadzone
   * 
   * @param deadzone Deadzone percentage (0-20 recommended)
   */
  void setDeadzone(double deadzone);
  
  /**
   * Set drive sensitivity
   * 
   * @param sensitivity Sensitivity multiplier (0.1-2.0 recommended)
   */
  void setSensitivity(double sensitivity);
  
  /**
   * Get current deadzone setting
   * 
   * @return Current deadzone percentage
   */
  double getDeadzone() const;
  
  /**
   * Get current sensitivity setting
   * 
   * @return Current sensitivity multiplier
   */
  double getSensitivity() const;
  
  // ========================================
  // Drive Control Methods
  // ========================================
  
  /**
   * Dual-stick arcade drive with smooth diagonal movement
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
  
  /**
   * Stop all drive motors
   */
  void stop();
};

#endif
