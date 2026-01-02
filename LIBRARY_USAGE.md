# Using Claw as a Library

This guide explains how to import Claw into your existing VEX V5 project to add double movement capabilities.

## What You Get

Claw provides a `ClawDrive` class that adds smooth diagonal/double movement to any 4-motor tank drive robot. Instead of forking this entire project, you can copy just the library files into your existing project.

## Quick Import Guide

### Step 1: Copy Library Files

Copy these two files to your project:

```
Your_Project/
├── include/
│   └── drive-control.h    ← Copy from Claw/include/
└── src/
    └── drive-control.cpp  ← Copy from Claw/src/
```

### Step 2: Create ClawDrive Instance

In your code (main.cpp or wherever you initialize your robot):

```cpp
#include "drive-control.h"

// Your existing motor definitions
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

// Create ClawDrive instance
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);
```

### Step 3: Use in Your Control Code

Replace your existing drive code with Claw methods:

**Before (without Claw):**
```cpp
void usercontrol(void) {
  while (true) {
    int forward = Controller1.Axis3.position();
    int turn = Controller1.Axis1.position();
    
    // Manual motor control
    LeftFront.spin(fwd, forward + turn, pct);
    LeftBack.spin(fwd, forward + turn, pct);
    RightFront.spin(fwd, forward - turn, pct);
    RightBack.spin(fwd, forward - turn, pct);
    
    wait(20, msec);
  }
}
```

**After (with Claw):**
```cpp
void usercontrol(void) {
  while (true) {
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    // Claw handles everything with smooth double movement!
    drive.arcadeDrive(forward, turn);
    
    wait(20, msec);
  }
}
```

That's it! Your robot now has smooth double movement.

## Complete Example

Here's a complete minimal example showing Claw integration:

```cpp
#include "vex.h"
#include "drive-control.h"

using namespace vex;

// Brain and controller
brain Brain;
controller Controller1;

// Define motors (adjust ports for your robot)
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

// Create ClawDrive instance
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

// Competition object
competition Competition;

void autonomous(void) {
  // Diagonal forward-right
  drive.arcadeDrive(60, 40);
  wait(2, seconds);
  
  // Stop
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
  
  while (true) {
    wait(100, msec);
  }
}
```

## Customization Options

### Setting Deadzone and Sensitivity

```cpp
// Option 1: Set in constructor
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack, 
                10.0,  // deadzone: 10%
                0.8);  // sensitivity: 80% speed

// Option 2: Set after creation
drive.setDeadzone(10.0);
drive.setSensitivity(0.8);
```

### Available Drive Methods

```cpp
// Arcade drive (recommended) - for smooth double movement
drive.arcadeDrive(forward, turn);

// Tank drive - independent left/right control
drive.tankDrive(leftSpeed, rightSpeed);

// Field-centric drive - for mecanum wheels
drive.fieldCentricDrive(forward, strafe, turn);

// Stop all motors
drive.stop();
```

## Integration Patterns

### Pattern 1: Minimal Integration

Add Claw to just your drive code:

```cpp
// Your existing robot code
#include "your-robot.h"
#include "drive-control.h"  // Add this

// Your existing setup...

// Add ClawDrive
ClawDrive drive(myLeftFront, myLeftBack, myRightFront, myRightBack);

// Use drive.arcadeDrive() in your control loop
```

### Pattern 2: Full Integration

Make Claw part of your robot class:

```cpp
class MyRobot {
private:
  motor leftFront, leftBack, rightFront, rightBack;
  ClawDrive drive;
  // ... other robot components
  
public:
  MyRobot() 
    : leftFront(PORT1), 
      leftBack(PORT2),
      rightFront(PORT3, true),
      rightBack(PORT4, true),
      drive(leftFront, leftBack, rightFront, rightBack) {
    // Robot initialization
  }
  
  void driveControl(double forward, double turn) {
    drive.arcadeDrive(forward, turn);
  }
};
```

### Pattern 3: Wrapper Functions

Create your own drive functions that use Claw:

```cpp
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

void myDrive(double forward, double turn) {
  // Add your custom logic here if needed
  // Then use Claw for the actual driving
  drive.arcadeDrive(forward, turn);
}

void myPrecisionDrive(double forward, double turn) {
  // Slow mode for precision
  drive.setSensitivity(0.5);
  drive.arcadeDrive(forward, turn);
  drive.setSensitivity(1.0);  // Reset
}
```

## Advantages Over Forking

✅ **Keep Your Project Structure** - No need to reorganize your code  
✅ **Easy Updates** - Just copy new versions of drive-control files  
✅ **Minimal Changes** - Add with just a few lines of code  
✅ **Your Motor Names** - Use your existing motor variables  
✅ **Your Port Numbers** - No need to match our configuration  
✅ **Mix and Match** - Use Claw for drive, keep your other systems  

## Troubleshooting

### Motors spin in wrong direction

```cpp
// Toggle the 'reversed' parameter (last argument)
motor RightFront = motor(PORT3, ratio18_1, true);   // Change to false
motor RightBack = motor(PORT4, ratio18_1, true);    // Change to false
```

### Robot turns when going straight

One side may be wired backward. Reverse one side:

```cpp
// If turning right when going straight:
motor LeftFront = motor(PORT1, ratio18_1, true);    // Add true
motor LeftBack = motor(PORT2, ratio18_1, true);     // Add true
```

### Diagonal movement too sensitive

Reduce sensitivity:

```cpp
drive.setSensitivity(0.7);  // 70% speed
```

### Controller drift affecting movement

Increase deadzone:

```cpp
drive.setDeadzone(10.0);  // 10% deadzone
```

## Next Steps

1. **Copy the files** to your project
2. **Create ClawDrive instance** with your motors
3. **Replace your drive code** with Claw methods
4. **Test and tune** sensitivity and deadzone
5. **Enjoy smooth double movement!**

For more examples, see:
- **EXAMPLES.md** - Various usage scenarios
- **CONFIGURATION.md** - Different robot configurations
- **src/main.cpp** - Complete working example

## Support

Questions? Issues? Suggestions?
- Open an issue on GitHub
- Check existing documentation
- Look at the example project

Happy building! 🤖
