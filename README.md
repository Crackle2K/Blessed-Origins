# Claw - Simple Double Movement Control System

A VEX V5 robot control system featuring smooth diagonal movement capabilities for enhanced maneuverability and control.

## Features

### Advanced Drive Control Systems

This project implements three different drive control methods to enable smooth diagonal movement:

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

## Project Structure

```
Claw/
├── include/
│   ├── robot-config.h      # Robot hardware configuration
│   └── drive-control.h     # Drive control function declarations
├── src/
│   ├── main.cpp            # Main robot program
│   ├── robot-config.cpp    # Hardware initialization
│   └── drive-control.cpp   # Drive control implementations
├── vex/
│   └── mkenv.mk           # Build environment
├── makefile               # Build configuration
└── Claw.v5code           # VEX project file
```

## Getting Started

### Hardware Requirements

- VEX V5 Brain
- VEX V5 Controller
- 4 Drive Motors (connected to ports 1-4)
- Standard tank drive or mecanum wheel configuration

### Motor Port Configuration

Default motor ports (can be modified in `src/robot-config.cpp`):
- **PORT1**: Left Front Motor
- **PORT2**: Left Back Motor  
- **PORT3**: Right Front Motor (reversed)
- **PORT4**: Right Back Motor (reversed)

### Installation

1. Open VEXcode V5
2. Open this project folder
3. Connect your V5 Brain
4. Download the program to your robot
5. Run and enjoy smooth diagonal movement!

## Configuration

### Adjusting Drive Sensitivity

Edit `src/robot-config.cpp`:

```cpp
const double DRIVE_SENSITIVITY = 1.0;  // Range: 0.1 to 2.0
```

- **Lower values** (0.5): Slower, more precise control
- **Higher values** (1.5): Faster, more aggressive driving

### Controller Deadzone

Edit `src/robot-config.cpp`:

```cpp
const double DRIVE_DEADZONE = 5.0;  // Range: 0 to 20
```

- Prevents controller drift
- Higher values = less sensitive to small movements

### Switching Drive Modes

Edit `src/main.cpp` in the `usercontrol()` function:

```cpp
// For Arcade Drive (default)
arcadeDrive(forward, turn);

// For Tank Drive (uncomment)
// tankDrive(leftSide, rightSide);

// For Field-Centric Drive (uncomment, requires mecanum)
// fieldCentricDrive(forward, strafe, turn);
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

The included autonomous routine demonstrates diagonal movement:

```cpp
// Diagonal forward-right
arcadeDrive(50, 30);

// Diagonal forward-left  
arcadeDrive(50, -30);
```

Modify the `autonomous()` function in `src/main.cpp` to create your own autonomous routines.

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

For 6-motor or 8-motor drives, modify `robot-config.cpp`:

```cpp
motor_group LeftDrive = motor_group(LeftFront, LeftBack, LeftMiddle);
motor_group RightDrive = motor_group(RightFront, RightBack, RightMiddle);
```

### Custom Control Curves

Add exponential curves for finer control at low speeds:

```cpp
double applyCurve(double input) {
  return input * input * input;  // Cubic curve
}
```

## Contributing

This is an open-source VEX robotics project. Feel free to:
- Report issues
- Suggest improvements
- Share your modifications
- Ask questions about implementation

## License

See LICENSE file for details.

## Credits

Developed for VEX Robotics Competition teams looking to improve their robot's maneuverability through smooth diagonal movement control.

---

**Need Help?** Check out the VEX Forum or VEX Robotics documentation for additional support.
