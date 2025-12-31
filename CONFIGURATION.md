# Configuration Guide for Different Robot Types

This guide helps you configure the diagonal movement system for different VEX robot drivetrain configurations.

## Quick Configuration Selector

Choose your robot type:

1. **Standard 4-Motor Tank Drive** (Most common)
2. **6-Motor Tank Drive** (High power)
3. **Mecanum Wheel Drive** (Omnidirectional)
4. **X-Drive** (Advanced omnidirectional)
5. **H-Drive** (Strafing capable)

---

## 1. Standard 4-Motor Tank Drive ✓ (Default)

**What it is**: Two motors on each side, standard wheels

**Current configuration**: ✓ Already set up!

```cpp
// src/robot-config.cpp
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);   // Reversed
motor RightBack = motor(PORT4, ratio18_1, true);    // Reversed
```

**Recommended Control**: Arcade Drive (default in main.cpp)

```cpp
// src/main.cpp - usercontrol()
double forward = Controller1.Axis3.position(percent);
double turn = Controller1.Axis1.position(percent);
arcadeDrive(forward, turn);
```

**Diagonal Movement**: ✓ Works perfectly with arcade drive

---

## 2. Six-Motor Tank Drive

**What it is**: Three motors on each side for more power

**When to use**: Heavy robots, need more torque

### Configuration Steps

**Step 1**: Update robot-config.h

```cpp
// include/robot-config.h
// Add after existing motor declarations:
extern motor LeftMiddle;
extern motor RightMiddle;

// OR use motor groups (recommended):
extern motor_group LeftDrive;
extern motor_group RightDrive;
```

**Step 2**: Update robot-config.cpp

**Option A: Individual Motors**
```cpp
// src/robot-config.cpp
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftMiddle = motor(PORT2, ratio18_1, false);
motor LeftBack = motor(PORT3, ratio18_1, false);
motor RightFront = motor(PORT4, ratio18_1, true);
motor RightMiddle = motor(PORT5, ratio18_1, true);
motor RightBack = motor(PORT6, ratio18_1, true);
```

**Option B: Motor Groups (Recommended)**
```cpp
// src/robot-config.cpp
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftMiddle = motor(PORT2, ratio18_1, false);
motor LeftBack = motor(PORT3, ratio18_1, false);

motor RightFront = motor(PORT4, ratio18_1, true);
motor RightMiddle = motor(PORT5, ratio18_1, true);
motor RightBack = motor(PORT6, ratio18_1, true);

motor_group LeftDrive = motor_group(LeftFront, LeftMiddle, LeftBack);
motor_group RightDrive = motor_group(RightFront, RightMiddle, RightBack);
```

**Step 3**: Update drive-control.cpp

If using motor groups:
```cpp
// src/drive-control.cpp - arcadeDrive function
void arcadeDrive(double forward, double turn) {
  forward = applyDeadzone(forward, DRIVE_DEADZONE);
  turn = applyDeadzone(turn, DRIVE_DEADZONE);
  
  forward *= DRIVE_SENSITIVITY;
  turn *= DRIVE_SENSITIVITY;
  
  double leftVelocity = clamp(forward + turn, -100.0, 100.0);
  double rightVelocity = clamp(forward - turn, -100.0, 100.0);
  
  LeftDrive.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  RightDrive.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
}
```

**Diagonal Movement**: ✓ Works the same as 4-motor

---

## 3. Mecanum Wheel Drive

**What it is**: Four wheels with diagonal rollers, can move in any direction

**When to use**: Need true omnidirectional movement

### Configuration Steps

**Step 1**: Verify motor connections
- Motors must be at 45° angles
- Rollers should form an "X" pattern when viewed from above

**Step 2**: No changes needed to robot-config files!

**Step 3**: Update main.cpp to use field-centric drive

```cpp
// src/main.cpp - usercontrol()
void usercontrol(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Mecanum Drive Active");
  
  while (true) {
    // Get all three control axes
    double forward = Controller1.Axis3.position(percent);  // Left Y
    double strafe = Controller1.Axis4.position(percent);   // Left X
    double turn = Controller1.Axis1.position(percent);     // Right X
    
    // Use field-centric drive for omnidirectional control
    fieldCentricDrive(forward, strafe, turn);
    
    wait(20, msec);
  }
}
```

**Diagonal Movement**: ✓✓ Best diagonal movement capability!

### Mecanum Control Tips
- Forward + Strafe = True diagonal (no rotation)
- Forward + Turn = Curved diagonal
- All three = Complex movement paths

---

## 4. X-Drive Configuration

**What it is**: Four wheels at 45° angles, omni wheels

**When to use**: Fast omnidirectional movement, good for offense

### Configuration Steps

**Step 1**: Update motor directions for X-Drive

```cpp
// src/robot-config.cpp
// X-Drive motors are at 45° angles
motor LeftFront = motor(PORT1, ratio18_1, false);
motor LeftBack = motor(PORT2, ratio18_1, true);    // Reversed
motor RightFront = motor(PORT3, ratio18_1, true);   // Reversed
motor RightBack = motor(PORT4, ratio18_1, false);
```

**Step 2**: Update field-centric drive for X-Drive kinematics

```cpp
// src/drive-control.cpp - Add new function
void xDrive(double forward, double strafe, double turn) {
  forward = applyDeadzone(forward, DRIVE_DEADZONE);
  strafe = applyDeadzone(strafe, DRIVE_DEADZONE);
  turn = applyDeadzone(turn, DRIVE_DEADZONE);
  
  forward *= DRIVE_SENSITIVITY;
  strafe *= DRIVE_SENSITIVITY;
  turn *= DRIVE_SENSITIVITY;
  
  // X-Drive kinematics (uses sqrt(2) factor)
  double leftFrontVelocity = forward + strafe + turn;
  double leftBackVelocity = forward - strafe + turn;
  double rightFrontVelocity = forward - strafe - turn;
  double rightBackVelocity = forward + strafe - turn;
  
  // Scale down if needed
  double maxVelocity = fmax(fmax(fabs(leftFrontVelocity), fabs(leftBackVelocity)),
                            fmax(fabs(rightFrontVelocity), fabs(rightBackVelocity)));
  
  if (maxVelocity > 100.0) {
    leftFrontVelocity = (leftFrontVelocity / maxVelocity) * 100.0;
    leftBackVelocity = (leftBackVelocity / maxVelocity) * 100.0;
    rightFrontVelocity = (rightFrontVelocity / maxVelocity) * 100.0;
    rightBackVelocity = (rightBackVelocity / maxVelocity) * 100.0;
  }
  
  LeftFront.spin(directionType::fwd, leftFrontVelocity, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, leftBackVelocity, velocityUnits::pct);
  RightFront.spin(directionType::fwd, rightFrontVelocity, velocityUnits::pct);
  RightBack.spin(directionType::fwd, rightBackVelocity, velocityUnits::pct);
}
```

**Step 3**: Use in main.cpp (same as mecanum)

**Diagonal Movement**: ✓✓ Excellent, faster than mecanum

---

## 5. H-Drive Configuration

**What it is**: Tank drive + center strafe wheel(s)

**When to use**: Want strafing but keep tank drive simplicity

### Configuration Steps

**Step 1**: Add strafe motor(s) to robot-config.h

```cpp
// include/robot-config.h
extern motor StrafeMotor;  // Or motor_group for two strafe motors
```

**Step 2**: Add to robot-config.cpp

```cpp
// src/robot-config.cpp
motor StrafeMotor = motor(PORT5, ratio18_1, false);
// Configure in configureRobot():
StrafeMotor.setStopping(brake);
```

**Step 3**: Create H-Drive control function

```cpp
// src/drive-control.cpp - Add new function
void hDrive(double forward, double strafe, double turn) {
  // Tank drive for forward/turn
  double tankForward = applyDeadzone(forward, DRIVE_DEADZONE);
  double tankTurn = applyDeadzone(turn, DRIVE_DEADZONE);
  
  tankForward *= DRIVE_SENSITIVITY;
  tankTurn *= DRIVE_SENSITIVITY;
  
  double leftVelocity = clamp(tankForward + tankTurn, -100.0, 100.0);
  double rightVelocity = clamp(tankForward - tankTurn, -100.0, 100.0);
  
  // Separate strafe control
  double strafeVelocity = applyDeadzone(strafe, DRIVE_DEADZONE);
  strafeVelocity = clamp(strafeVelocity * DRIVE_SENSITIVITY, -100.0, 100.0);
  
  LeftFront.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, leftVelocity, velocityUnits::pct);
  RightFront.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
  RightBack.spin(directionType::fwd, rightVelocity, velocityUnits::pct);
  StrafeMotor.spin(directionType::fwd, strafeVelocity, velocityUnits::pct);
}
```

**Step 4**: Use in main.cpp

```cpp
double forward = Controller1.Axis3.position(percent);
double strafe = Controller1.Axis4.position(percent);
double turn = Controller1.Axis1.position(percent);
hDrive(forward, strafe, turn);
```

**Diagonal Movement**: ✓ Good, combines tank curves with strafing

---

## Motor Port Reference

### Common VEX V5 Port Layouts

**Standard 4-Motor**:
```
LEFT SIDE:        RIGHT SIDE:
PORT1 - LF        PORT3 - RF
PORT2 - LB        PORT4 - RB
```

**6-Motor Drive**:
```
LEFT SIDE:        RIGHT SIDE:
PORT1 - LF        PORT4 - RF
PORT2 - LM        PORT5 - RM
PORT3 - LB        PORT6 - RB
```

**Mecanum/X-Drive**:
```
FRONT:
PORT1 - LF ╱   ╲ RF - PORT3

BACK:
PORT2 - LB ╲   ╱ RB - PORT4
```

---

## Gear Ratio Selection

Choose gear ratio based on your needs:

| Ratio | Speed | Torque | Best For |
|-------|-------|--------|----------|
| 36:1 | Slow | High | Heavy robots, climbing |
| 18:1 | Medium | Medium | **General use (default)** |
| 6:1 | Fast | Low | Lightweight, speed-focused |

Update in robot-config.cpp:
```cpp
motor LeftFront = motor(PORT1, ratio18_1, false);  // Change ratio here
//                            ↑
//                   ratio36_1, ratio18_1, or ratio6_1
```

---

## Troubleshooting

### Problem: Robot turns when going "straight"
**Solution**: One side is wired backward
```cpp
// Try reversing one side in robot-config.cpp
motor RightFront = motor(PORT3, ratio18_1, true);  // Toggle this
```

### Problem: Robot goes backward when joystick pushed forward
**Solution**: Reverse all motors
```cpp
motor LeftFront = motor(PORT1, ratio18_1, true);   // Add 'true'
motor LeftBack = motor(PORT2, ratio18_1, true);
motor RightFront = motor(PORT3, ratio18_1, false); // Remove 'true'
motor RightBack = motor(PORT4, ratio18_1, false);
```

### Problem: Mecanum wheels don't strafe correctly
**Solution**: Check wheel orientation - rollers should form X pattern
```
Top view:
  ╱ ╲    Correct X pattern
  ╲ ╱
```

### Problem: Diagonal movement too sensitive
**Solution**: Reduce sensitivity
```cpp
// src/robot-config.cpp
const double DRIVE_SENSITIVITY = 0.7;  // Reduce from 1.0
```

---

## Testing Your Configuration

Run this test in autonomous to verify correct setup:

```cpp
void testConfiguration(void) {
  Brain.Screen.print("Testing configuration...");
  
  // Test 1: Forward
  arcadeDrive(50, 0);
  wait(1, seconds);
  arcadeDrive(0, 0);
  wait(0.5, seconds);
  // Should move straight forward
  
  // Test 2: Turn right
  arcadeDrive(0, 50);
  wait(1, seconds);
  arcadeDrive(0, 0);
  wait(0.5, seconds);
  // Should rotate clockwise
  
  // Test 3: Diagonal forward-right
  arcadeDrive(50, 50);
  wait(1, seconds);
  arcadeDrive(0, 0);
  // Should curve forward-right smoothly
  
  Brain.Screen.print("Test complete!");
}
```

If any test fails, check your motor directions and ports!

---

## Summary Table

| Drive Type | Motors | Diagonal? | Strafe? | Complexity |
|------------|--------|-----------|---------|------------|
| 4-Motor Tank | 4 | ✓ Good | ✗ | Low |
| 6-Motor Tank | 6 | ✓ Good | ✗ | Low |
| Mecanum | 4 | ✓✓ Best | ✓ | Medium |
| X-Drive | 4 | ✓✓ Best | ✓ | Medium |
| H-Drive | 5-6 | ✓ Good | ✓ | Medium |

**Recommendation**: Start with standard 4-motor tank drive and arcade control. It provides excellent diagonal movement with the simplest configuration!
