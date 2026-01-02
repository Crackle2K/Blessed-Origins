# Diagonal Movement Examples

This document provides practical examples of how to use the Claw Drive Control Library in various scenarios.

## Basic Usage Examples

### Example 1: Simple Diagonal Movement in Autonomous

```cpp
void autonomous(void) {
  // Assuming you have created a ClawDrive instance called 'drive'
  
  // Move forward-right diagonal for 2 seconds
  // 70% forward, 40% right turn
  drive.arcadeDrive(70, 40);
  wait(2, seconds);
  
  // Stop
  drive.stop();
  wait(0.5, seconds);
  
  // Move backward-left diagonal for 2 seconds  
  // -60% backward, -30% left turn
  drive.arcadeDrive(-60, -30);
  wait(2, seconds);
  
  // Stop
  drive.stop();
}
```

### Example 2: Smooth Curved Path

```cpp
void autonomous(void) {
  // Start moving forward
  drive.arcadeDrive(80, 0);
  wait(1, seconds);
  
  // Gradually increase turn while maintaining forward speed
  // Creates a smooth spiral/curve
  for (int turn = 0; turn <= 60; turn += 5) {
    drive.arcadeDrive(80, turn);
    wait(0.1, seconds);
  }
  
  // Stop
  drive.stop();
}
```

### Example 3: Square with Rounded Corners

```cpp
void autonomous(void) {
  // Move forward
  drive.arcadeDrive(60, 0);
  wait(1.5, seconds);
  
  // Diagonal turn (rounded corner)
  drive.arcadeDrive(40, 50);
  wait(0.8, seconds);
  
  // Forward again
  drive.arcadeDrive(60, 0);
  wait(1.5, seconds);
  
  // Another rounded corner
  drive.arcadeDrive(40, 50);
  wait(0.8, seconds);
  
  // Continue pattern...
  drive.stop();
}
```

## Advanced Control Examples

### Example 4: Field-Centric Strafing (Mecanum Wheels)

```cpp
void usercontrol(void) {
  // Create ClawDrive instance with your motors
  ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);
  
  while (true) {
    double forward = Controller1.Axis3.position(percent);  // Forward/Back
    double strafe = Controller1.Axis4.position(percent);   // Left/Right
    double turn = Controller1.Axis1.position(percent);     // Rotation
    
    // Robot can move in any direction while rotating independently
    drive.fieldCentricDrive(forward, strafe, turn);
    
    wait(20, msec);
  }
}
```

### Example 5: Precision Diagonal Approach

```cpp
void approachTarget(void) {
  // Useful for approaching game objects at an angle
  
  // Fast diagonal approach
  drive.arcadeDrive(90, 30);
  wait(1.5, seconds);
  
  // Slow down for precision
  drive.arcadeDrive(40, 15);
  wait(1, seconds);
  
  // Fine adjustment
  drive.arcadeDrive(20, 10);
  wait(0.5, seconds);
  
  // Stop at target
  drive.stop();
}
```

### Example 6: Dynamic Speed Adjustment

```cpp
void usercontrol(void) {
  ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);
  bool slowMode = false;
  
  while (true) {
    // Toggle slow mode with button
    if (Controller1.ButtonA.pressing()) {
      slowMode = !slowMode;
      
      if (slowMode) {
        drive.setSensitivity(0.5);  // 50% speed
      } else {
        drive.setSensitivity(1.0);  // 100% speed
      }
      
      wait(0.3, seconds); // Debounce
    }
    
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    drive.arcadeDrive(forward, turn);
    wait(20, msec);
  }
}
```

## Competition Scenarios

### Example 7: Skills Run with Diagonal Movements

```cpp
void autonomous(void) {
  // Assuming ClawDrive instance 'drive' exists
  
  // Start position to first goal (diagonal approach)
  drive.arcadeDrive(75, 35);
  wait(2.2, seconds);
  
  // Score at goal
  drive.stop();
  scoreGoal(); // Your scoring function
  wait(1, seconds);
  
  // Back up diagonally to next position
  drive.arcadeDrive(-60, -25);
  wait(1.8, seconds);
  
  // Turn to face next target
  drive.arcadeDrive(0, 70);
  wait(0.6, seconds);
  
  // Straight to next goal
  drive.arcadeDrive(80, 0);
  wait(1.5, seconds);
  
  drive.stop();
}
```

### Example 8: Defensive Diagonal Movement

```cpp
void usercontrol(void) {
  ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);
  
  while (true) {
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    // Enhanced turning for defensive maneuvers
    if (Controller1.ButtonR1.pressing()) {
      // Boost sensitivity for quick evasion
      drive.setSensitivity(1.5);
      drive.arcadeDrive(forward, turn);
      drive.setSensitivity(1.0);  // Reset
    } else {
      drive.arcadeDrive(forward, turn);
    }
    
    wait(20, msec);
  }
}
```

### Example 9: Smooth Slalom Course

```cpp
void autonomous(void) {
  // Navigate through cones in a slalom pattern
  
  // Start straight
  drive.arcadeDrive(70, 0);
  wait(0.8, seconds);
  
  // Weave right
  drive.arcadeDrive(60, 40);
  wait(0.6, seconds);
  
  // Straighten briefly
  drive.arcadeDrive(70, 0);
  wait(0.4, seconds);
  
  // Weave left
  drive.arcadeDrive(60, -40);
  wait(0.6, seconds);
  
  // Straighten
  drive.arcadeDrive(70, 0);
  wait(0.4, seconds);
  
  // Repeat pattern...
  
  drive.stop();
}
```

## Complete Integration Example

### Example 10: Full Robot with Claw Library

```cpp
#include "vex.h"
#include "drive-control.h"

using namespace vex;

// Hardware definitions
brain Brain;
controller Controller1;

motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

// Create ClawDrive instance
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

// Competition object
competition Competition;

void pre_auton(void) {
  // Configure motors
  LeftFront.setStopping(brake);
  LeftBack.setStopping(brake);
  RightFront.setStopping(brake);
  RightBack.setStopping(brake);
  
  // Optional: customize Claw settings
  drive.setDeadzone(5.0);
  drive.setSensitivity(1.0);
}

void autonomous(void) {
  // Diagonal movements in autonomous
  drive.arcadeDrive(60, 30);
  wait(2, seconds);
  
  drive.arcadeDrive(60, -30);
  wait(2, seconds);
  
  drive.stop();
}

void usercontrol(void) {
  while (true) {
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    drive.arcadeDrive(forward, turn);
    
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  pre_auton();
  
  while (true) {
    wait(100, msec);
  }
}
```
```

## Tips for Each Example

### For Autonomous Programming:
- Start with shorter wait times and increase gradually
- Test diagonal angles in small increments (10%, 20%, 30%, etc.)
- Record actual times and distances on your practice field
- Fine-tune values based on battery level and carpet/tile surface

### For Driver Control:
- Practice smooth stick movements rather than rapid changes
- Learn to anticipate: start your turn before reaching the target
- Combine forward and turn inputs gradually for smoother arcs
- Use lower speeds when learning, increase as skill improves

### For Competition:
- Create reusable functions for common diagonal movements
- Use constants for frequently-used speed/turn combinations
- Test autonomous routines multiple times for consistency
- Have backup straight-line paths if diagonal timing is off

## Mathematical Reference

### Converting Angles to Arcade Drive Values

If you want to move at a specific angle:

```cpp
// For a 45-degree diagonal (forward-right)
arcadeDrive(70, 70);  // Equal forward and turn

// For a 30-degree angle (mostly forward, slight right)
arcadeDrive(87, 50);  // More forward, less turn

// For a 60-degree angle (turning more than forward)
arcadeDrive(50, 87);  // Less forward, more turn
```

### Speed Relationships

```cpp
// Gentle arc (mostly straight)
forward = 100, turn = 20   // ~11° angle

// Moderate diagonal
forward = 70, turn = 70    // ~45° angle

// Sharp turn
forward = 20, turn = 100   // ~79° angle
```

## Testing Your Diagonal Movement

### Quick Test Routine

```cpp
void testDiagonals(void) {
  Brain.Screen.print("Testing diagonals...");
  
  // Test 1: Forward-right
  arcadeDrive(60, 40);
  wait(1, seconds);
  arcadeDrive(0, 0);
  wait(0.5, seconds);
  
  // Test 2: Forward-left
  arcadeDrive(60, -40);
  wait(1, seconds);
  arcadeDrive(0, 0);
  wait(0.5, seconds);
  
  // Test 3: Backward-right
  arcadeDrive(-60, 40);
  wait(1, seconds);
  arcadeDrive(0, 0);
  wait(0.5, seconds);
  
  // Test 4: Backward-left
  arcadeDrive(-60, -40);
  wait(1, seconds);
  arcadeDrive(0, 0);
  
  Brain.Screen.print("Test complete!");
}
```

Place tape on your field in an X pattern and run this test to verify smooth diagonal movement in all four directions.
