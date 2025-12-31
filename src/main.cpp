/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Claw                                                      */
/*    Created:      2025                                                      */
/*    Description:  VEX V5 Robot Program with Diagonal Movement Support      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"
#include "drive-control.h"

using namespace vex;

// Competition object for managing match states
competition Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Configure robot hardware
  configureRobot();
  
  // Display information on the Brain screen
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Claw Robot Ready");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Diagonal Drive Enabled");
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // Example autonomous routine demonstrating diagonal movement
  
  // Move forward for 1 second
  arcadeDrive(50, 0);
  wait(1, seconds);
  
  // Diagonal movement: forward-right for 1 second
  arcadeDrive(50, 30);
  wait(1, seconds);
  
  // Turn in place for 0.5 seconds
  arcadeDrive(0, 50);
  wait(0.5, seconds);
  
  // Diagonal movement: forward-left for 1 second
  arcadeDrive(50, -30);
  wait(1, seconds);
  
  // Stop
  arcadeDrive(0, 0);
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // Display control information
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Driver Control Active");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Arcade Drive Mode");
  
  while (true) {
    // Method 1: Arcade Drive (Recommended for smooth diagonal movement)
    // Left stick Y-axis: Forward/Backward
    // Right stick X-axis: Left/Right turning
    // When both are active, the robot moves diagonally smoothly
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    arcadeDrive(forward, turn);
    
    // Alternative Method 2: Tank Drive
    // Uncomment the following lines to use tank drive instead
    // This also supports diagonal movement by varying left/right speeds
    /*
    double leftSide = Controller1.Axis3.position(percent);
    double rightSide = Controller1.Axis2.position(percent);
    tankDrive(leftSide, rightSide);
    */
    
    // Alternative Method 3: Field-Centric Drive (for mecanum/X-drive)
    // Uncomment the following lines if you have mecanum wheels or X-drive
    /*
    double forward = Controller1.Axis3.position(percent);
    double strafe = Controller1.Axis4.position(percent);
    double turn = Controller1.Axis1.position(percent);
    fieldCentricDrive(forward, strafe, turn);
    */
    
    // Small delay to prevent CPU hogging
    wait(20, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                  Main                                     */
/*---------------------------------------------------------------------------*/

int main() {
  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function
  pre_auton();
  
  // Prevent main from exiting with an infinite loop
  while (true) {
    wait(100, msec);
  }
}
