# Claw - Double Movement Control Library for VEX V5

A VEX V5 library that adds smooth double (diagonal) movement capabilities to your robot. Import Claw into your project to enable advanced drive control without forking!

## What is Double Movement?

Double movement (also known as diagonal movement) allows your robot to move smoothly in any direction by combining forward/backward motion with turning. Instead of moving in discrete directions, your robot can execute smooth arcs and diagonal paths.

## Features

### Easy Library Integration

Claw is designed as a **library** that you can import into your own VEX V5 projects:

```cpp
#include "drive-control.h"

// Create ClawDrive with your motors
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

// Use in your code
drive.arcadeDrive(forward, turn);  // Instant double movement!
```

### Three Drive Control Methods

### Three Drive Control Methods

This library implements three different drive control methods:

#### 1. **Arcade Drive** (Recommended)
- **Left Stick Y-axis**: Forward/Backward movement
- **Right Stick X-axis**: Left/Right turning
- **Diagonal Movement**: Automatically achieved by using both sticks simultaneously
- **Best for**: Most VEX competitions - intuitive and smooth

Example: Push forward on left stick + right on right stick = smooth forward-right diagonal movement

#### 2. **Tank Drive**
- **Left Stick Y-axis**: Left side motors
- **Right Stick Y-axis**: Right side motors  
- **Diagonal Movement**: Set different speeds for each side
- **Best for**: Precise control and experienced drivers

Example: Left stick at 50%, right stick at 75% = diagonal movement to the right

#### 3. **Field-Centric Drive** (Advanced)
- **Left Stick Y-axis**: Forward/Backward
- **Left Stick X-axis**: Left/Right strafe
- **Right Stick X-axis**: Rotation
- **Diagonal Movement**: True omnidirectional movement
- **Best for**: Mecanum wheels or X-drive configurations
- **Note**: Requires special wheel configuration

## How Diagonal Movement Works

### The Math Behind Smooth Diagonals

Traditional tank drive can feel "clunky" when trying to move diagonally because you're manually adjusting two separate controls. Our arcade drive system uses **vector addition** to automatically calculate the perfect motor speeds for any direction:

```
Left Motor Speed = Forward + Turn
Right Motor Speed = Forward - Turn
```

This formula creates smooth diagonal arcs by combining:
- **Pure Forward** (Turn = 0): Both sides equal speed
- **Pure Turn** (Forward = 0): Opposite speeds for rotation
- **Diagonal** (Both active): Different speeds create an arc

### Example Scenarios

| Forward | Turn | Result |
|---------|------|--------|
| 50% | 0% | Straight forward at 50% |
| 50% | 30% | Forward-right diagonal arc |
| 50% | -30% | Forward-left diagonal arc |
| 0% | 50% | Rotate clockwise in place |
| 100% | 50% | Sharp forward-right curve |

## Quick Start - Adding Claw to Your Project

### Step 1: Copy Library Files

Copy these files to your VEX V5 project:
- `include/drive-control.h`
- `src/drive-control.cpp`

### Step 2: Include and Initialize

In your main.cpp:

```cpp
#include "drive-control.h"

// Create your motors (adjust ports as needed)
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

// Create ClawDrive instance
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

// Optional: Customize settings
// drive.setDeadzone(5.0);      // Default: 5.0
// drive.setSensitivity(1.0);   // Default: 1.0
```

### Step 3: Use in Your Control Code

```cpp
void usercontrol(void) {
  while (true) {
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    // Enable double movement with one line!
    drive.arcadeDrive(forward, turn);
    
    wait(20, msec);
  }
}
```

That's it! Your robot now has smooth double movement capabilities.

## Example Project Structure

## Example Project Structure

This repository includes a complete example robot project:
This repository includes a complete example robot project:

```
Claw/
├── include/
│   ├── robot-config.h      # Example robot hardware configuration
│   └── drive-control.h     # Claw library header (COPY THIS)
├── src/
│   ├── main.cpp            # Example robot program
│   ├── robot-config.cpp    # Example hardware initialization
│   └── drive-control.cpp   # Claw library implementation (COPY THIS)
└── ...
```

**Library Files** (copy these to your project):
- `include/drive-control.h`
- `src/drive-control.cpp`

**Example Files** (reference for usage):
- `src/main.cpp` - Shows how to use the library
- `include/robot-config.h` and `src/robot-config.cpp` - Example motor setup

## Using Claw as a Library

### Option 1: Copy Files (Recommended)

1. **Copy library files** to your existing VEX project:
   - Copy `include/drive-control.h` to your project's `include/` folder
   - Copy `src/drive-control.cpp` to your project's `src/` folder

2. **Create ClawDrive instance** with your motors:
   ```cpp
   #include "drive-control.h"
   
   ClawDrive drive(myLeftFront, myLeftBack, myRightFront, myRightBack);
   ```

3. **Use the drive methods** in your control code:
   ```cpp
   drive.arcadeDrive(forward, turn);
   ```

### Option 2: Fork and Modify

1. Fork this repository
2. Modify `robot-config.cpp` for your robot's hardware
3. Modify `main.cpp` for your robot's logic
4. The library is already integrated!

## Library API Reference

### ClawDrive Class

#### Constructor
```cpp
ClawDrive(motor& leftFront, motor& leftBack, 
          motor& rightFront, motor& rightBack,
          double deadzone = 5.0, double sensitivity = 1.0)
```

#### Configuration Methods
```cpp
void setDeadzone(double deadzone);      // Set controller deadzone (0-20)
void setSensitivity(double sensitivity); // Set drive sensitivity (0.1-2.0)
double getDeadzone() const;             // Get current deadzone
double getSensitivity() const;          // Get current sensitivity
```

#### Drive Control Methods
```cpp
// Arcade drive (recommended) - smooth diagonal movement
void arcadeDrive(double forward, double turn);

// Tank drive - independent side control
void tankDrive(double left, double right);

// Field-centric drive - for mecanum/X-drive (omnidirectional)
void fieldCentricDrive(double forward, double strafe, double turn);

// Stop all motors
void stop();
```

## Getting Started

### Hardware Requirements

### Hardware Requirements

- VEX V5 Brain
- VEX V5 Controller
- 4 Drive Motors (minimum)
- Standard tank drive or mecanum wheel configuration

### Installing the Library

**Method 1: Copy to Existing Project**

1. Download or clone this repository
2. Copy `include/drive-control.h` to your project's `include/` directory
3. Copy `src/drive-control.cpp` to your project's `src/` directory
4. Include the header in your code: `#include "drive-control.h"`

**Method 2: Use This Project as a Template**

1. Clone/download this repository
2. Open in VEXcode V5
3. Modify `robot-config.cpp` for your motor ports
4. Modify `main.cpp` for your robot's autonomous and driver control
5. The library is already integrated!

### Basic Usage Example

```cpp
#include "vex.h"
#include "drive-control.h"

using namespace vex;

// Define your motors
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightBack = motor(PORT4, ratio18_1, true);

// Create ClawDrive instance
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack);

int main() {
  controller Controller1;
  
  while (true) {
    // Get controller input
    double forward = Controller1.Axis3.position(percent);
    double turn = Controller1.Axis1.position(percent);
    
    // Drive with smooth double movement
    drive.arcadeDrive(forward, turn);
    
    wait(20, msec);
  }
}
```

## Configuration

### Adjusting Drive Sensitivity

```cpp
// Create drive with custom sensitivity
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack, 5.0, 0.8);

// Or adjust after creation
drive.setSensitivity(0.8);  // 80% speed
```

- **Lower values** (0.5): Slower, more precise control
- **Higher values** (1.5): Faster, more aggressive driving
- **Default**: 1.0 (100%)

### Controller Deadzone

```cpp
// Create drive with custom deadzone
ClawDrive drive(LeftFront, LeftBack, RightFront, RightBack, 10.0);

// Or adjust after creation
drive.setDeadzone(10.0);  // 10% deadzone
```

- Prevents controller drift
- Higher values = less sensitive to small movements
- **Default**: 5.0 (5%)

### Motor Port Configuration

Adjust motor ports in your robot-config or where you create motors:
Adjust motor ports in your robot-config or where you create motors:

```cpp
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);    // Note: reversed
motor RightBack = motor(PORT4, ratio18_1, true);     // Note: reversed
```

**Default Configuration:**
- **PORT1**: Left Front Motor
- **PORT2**: Left Back Motor  
- **PORT3**: Right Front Motor (reversed)
- **PORT4**: Right Back Motor (reversed)

### Installation

1. Open VEXcode V5
2. Open this project folder or your own project with Claw files copied
3. Connect your V5 Brain
4. Download the program to your robot
5. Run and enjoy smooth diagonal movement!

## Configuration

### Switching Drive Modes

Choose your preferred drive mode:

Choose your preferred drive mode:

```cpp
// For Arcade Drive (default, recommended)
drive.arcadeDrive(forward, turn);

// For Tank Drive
// double leftSide = Controller1.Axis3.position(percent);
// double rightSide = Controller1.Axis2.position(percent);
// drive.tankDrive(leftSide, rightSide);

// For Field-Centric Drive (requires mecanum wheels)
// double forward = Controller1.Axis3.position(percent);
// double strafe = Controller1.Axis4.position(percent);
// double turn = Controller1.Axis1.position(percent);
// drive.fieldCentricDrive(forward, strafe, turn);
```

## Usage Tips

### For Competition Drivers

1. **Practice gradually**: Start with gentle inputs, then progress to full stick deflection
2. **Smooth is fast**: Gentle curves are often faster than sharp turns
3. **Use both sticks**: Don't just use one - combining them gives you full control
4. **Muscle memory**: Practice the same movements to build consistency

### Common Diagonal Maneuvers

- **Forward-right arc**: Left stick forward + Right stick right
- **Forward-left arc**: Left stick forward + Right stick left
- **Backward-right arc**: Left stick back + Right stick right
- **Backward-left arc**: Left stick back + Right stick left

## Autonomous Mode

The library works seamlessly in autonomous mode:

```cpp
void autonomous(void) {
  // Diagonal forward-right for 2 seconds
  drive.arcadeDrive(50, 30);
  wait(2, seconds);
  
  // Diagonal forward-left for 2 seconds
  drive.arcadeDrive(50, -30);
  wait(2, seconds);
  
  // Stop
  drive.stop();
}
```

See `src/main.cpp` for a complete autonomous example.

## Troubleshooting

### Robot doesn't move diagonally smoothly

- **Check motor directions**: Some motors may need to be reversed
- **Verify wiring**: Ensure all motors are connected to correct ports
- **Adjust deadzone**: Controller drift can affect diagonal movement

### Robot turns too fast/slow when going diagonal

- Adjust `DRIVE_SENSITIVITY` in `robot-config.cpp`
- Try different Forward/Turn ratios in your controller inputs

### Motors run at different speeds

- Check gear ratios match between motors
- Verify motors are same model/type
- Adjust individual motor reversals in config

## Advanced Customization

### Adding Motor Groups

For 6-motor or 8-motor drives:

```cpp
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftMiddle = motor(PORT2, ratio18_1, false);
motor LeftBack = motor(PORT3, ratio18_1, false);
motor RightFront = motor(PORT4, ratio18_1, true);
motor RightMiddle = motor(PORT5, ratio18_1, true);
motor RightBack = motor(PORT6, ratio18_1, true);

motor_group LeftDrive = motor_group(LeftFront, LeftMiddle, LeftBack);
motor_group RightDrive = motor_group(RightFront, RightMiddle, RightBack);

// Note: ClawDrive currently requires 4 individual motor references
// For motor groups, you'll need to adapt the code or use individual motors
```

### Custom Control Curves

Add exponential curves for finer control at low speeds:

```cpp
double applyCurve(double input) {
  return input * input * input;  // Cubic curve
}
```

## Contributing

This is an open-source VEX robotics library. Feel free to:
- Report issues
- Suggest improvements
- Submit pull requests
- Share your implementations
- Ask questions about usage

## Support and Documentation

- **EXAMPLES.md** - Code examples for different scenarios
- **CONFIGURATION.md** - Detailed configuration guide for different robot types
- **QUICK_REFERENCE.md** - Quick reference guide
- **VISUAL_GUIDE.md** - Visual guide to double movement

## Why Use Claw?

✅ **Easy Integration** - Just copy 2 files to your project  
✅ **No Forking Required** - Keep your own project structure  
✅ **Clean API** - Simple, intuitive class-based interface  
✅ **Flexible** - Works with any VEX V5 drivetrain  
✅ **Well Documented** - Extensive docs and examples  
✅ **Competition Tested** - Proven in VEX competitions  

## License

See LICENSE file for details.

## Credits

Developed for VEX Robotics Competition teams looking to add smooth double movement to their robots without forking or restructuring their projects.

**Import Claw, enable double movement, compete better!**

---

**Need Help?** Check out the documentation files or open an issue on GitHub.
