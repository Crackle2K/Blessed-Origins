# Understanding Diagonal Movement: Visual Guide

## What is Diagonal Movement?

Diagonal movement allows your VEX robot to move in any direction smoothly, not just forward/backward and turn. This is achieved by combining forward/backward motion with turning motion.

## Visual Representation

```
         Forward (100%)
              ^
              |
              |
    NW        |       NE
       \      |      /
         \    |    /
           \  |  /
             \|/
Left <--------+--------> Right
Turn          /|\       Turn
(-100%)     /  |  \      (100%)
          /    |    \
        /      |      \
      SW        |        SE
              |
              |
              v
         Backward (-100%)
```

## How Controller Inputs Create Diagonal Movement

### Arcade Drive Mode

```
Controller Layout:
┌─────────────────────────────────┐
│  VEX Controller                 │
│                                 │
│    Left Stick    Right Stick    │
│       (Y)           (X)         │
│        ^             <>         │
│       <+>                       │
│        v                        │
│                                 │
│  Y = Forward/Back               │
│  X = Turn Left/Right            │
└─────────────────────────────────┘
```

### Movement Examples

#### 1. Forward Only
```
Left Y: 100%    Right X: 0%
Result: Straight forward

Left Motor:  100%  (100 + 0)
Right Motor: 100%  (100 - 0)
```

#### 2. Turn Right Only
```
Left Y: 0%      Right X: 50%
Result: Rotate clockwise

Left Motor:  50%   (0 + 50)
Right Motor: -50%  (0 - 50)
```

#### 3. Forward-Right Diagonal
```
Left Y: 80%     Right X: 40%
Result: Smooth diagonal arc (forward-right)

Left Motor:  120% > 100% (clamped)  (80 + 40)
Right Motor:  40%                   (80 - 40)

The robot curves forward-right smoothly!
```

#### 4. Forward-Left Diagonal
```
Left Y: 80%     Right X: -40%
Result: Smooth diagonal arc (forward-left)

Left Motor:   40%                   (80 - 40)
Right Motor: 120% > 100% (clamped)  (80 + 40)

The robot curves forward-left smoothly!
```

## The Math Behind It

### Basic Formula
```
Left Motor Speed  = Forward + Turn
Right Motor Speed = Forward - Turn
```

### Example Calculations

**Scenario: Gentle Forward-Right Curve**
- Forward input: 60%
- Turn input: 20%

```
Left Motor  = 60 + 20 = 80%  (Faster)
Right Motor = 60 - 20 = 40%  (Slower)
```

Result: Robot moves forward while gradually turning right (smooth arc)

**Scenario: Sharp Forward-Right Turn**
- Forward input: 50%
- Turn input: 60%

```
Left Motor  = 50 + 60 = 110% > 100% (clamped)  (Full speed)
Right Motor = 50 - 60 = -10%                   (Slight reverse)
```

Result: Robot makes a sharp right turn while moving forward

**Scenario: Backward-Left Diagonal**
- Forward input: -70%
- Turn input: -30%

```
Left Motor  = -70 + (-30) = -100%  (Full reverse)
Right Motor = -70 - (-30) = -40%   (Slower reverse)
```

Result: Robot moves backward while turning left

## Comparison: With vs Without Diagonal Movement

### WITHOUT Diagonal Movement (Old Method)
```
Step 1: Move forward
   ^
   ^
   
Step 2: Stop, then turn right
      >
      
Step 3: Move forward again
         ^
         ^

Result: Robot "stutters" - inefficient and slow
```

### WITH Diagonal Movement (New Method)
```
Single smooth motion:
   ^
    NE
      NE
        >

Result: Smooth arc - faster and more efficient
```

## Field-Centric Drive (Advanced)

For robots with mecanum wheels or X-drive:

```
         Strafe Left
              <
              |
    NW        |       NE
       \      |      /
         \    |    /  Forward
           \  |  /     ^
             \|/
Turn  CCW-----+-----CW  Turn
              /|\
            /  |  \
          /    |    \
        /      |      \
      SW        |        SE
              |
              >
         Strafe Right
```

With field-centric drive, you can:
- Move in ANY direction while independently rotating
- Strafe sideways while facing forward
- Circle around an object while always facing it

## Practical Applications

### Competition Scenarios

#### Scenario 1: Approaching a Goal at an Angle
```
Start:  [Robot] ---> (diagonal) [Goal]

Without diagonal: 
  Forward > Stop > Turn > Forward
  Time: ~3 seconds

With diagonal:
  Forward + Turn (simultaneous)
  Time: ~1.5 seconds
  
Time saved: 50%!
```

#### Scenario 2: Navigating Around Obstacles
```
        [Obstacle]
           ###
    NE  <--  NW
   /         \
[Start]    [Goal]

Smooth curved path around obstacle
instead of multiple straight segments
```

#### Scenario 3: Defense/Offense Positioning
```
Your Robot: [R]    Opponent: [O]

Quick diagonal retreat:
    [R]  ->  SE   (Moving back and to side simultaneously)
[O] ^         [R]

Faster repositioning than back-then-turn
```

## Tips for Drivers

### Beginner Tips
1. Start with gentle inputs (30-50% on each stick)
2. Practice figure-8 patterns to get comfortable
3. Focus on smooth stick movements, not jerky changes

### Intermediate Tips
1. Learn to anticipate - start turning before you need to
2. Combine full forward with partial turn for wide arcs
3. Use equal forward/turn (e.g., 70%/70%) for 45° diagonals

### Advanced Tips
1. Vary speed mid-turn for spiral patterns
2. Quick direction changes: reverse one input while maintaining the other
3. Use diagonal movement for defensive positioning

## Testing Your Understanding

Try these exercises on your practice field:

### Exercise 1: Box with Rounded Corners
```
Start: [R]

  .---->.
  ^     v
  '<----'
  
Use diagonal movement at corners instead of stopping to turn
```

### Exercise 2: Slalom Course
```
Start: [R]

  NE-.  .-NW-.  .-NE
     v  v   v  v
  Cone  Cone  Cone
  
Weave through cones using alternating diagonal movements
```

### Exercise 3: Circle a Point
```
         ^
      NW  |  NE
    <----[+]---->
      SW  |  SE
         v
         
Keep robot facing center [X] while moving in a circle
(Requires field-centric drive or advanced arcade control)
```

## Common Mistakes and Solutions

### Mistake 1: Too Much Turn Input
```
Problem: Robot spinning instead of smooth diagonal
Forward: 50%  Turn: 90%

Solution: Reduce turn input relative to forward
Forward: 70%  Turn: 40%
```

### Mistake 2: Jerky Stick Movements
```
Problem: Robot stutters and wobbles

Solution: Move sticks smoothly and gradually
Practice: Trace circles with your thumb on the stick
```

### Mistake 3: Not Using Diagonal When Beneficial
```
Problem: Still driving like old method (forward > turn > forward)

Solution: Think in terms of curves, not corners
Ask: "Can I combine these movements?"
```

## Summary

**Diagonal movement** is achieved by running left and right motors at different speeds. The arcade drive formula automatically calculates the perfect speeds for any direction you want to go.

**Key Takeaway**: 
```
Different motor speeds = Diagonal movement
Left Motor != Right Motor = Curved path
Left Motor = Right Motor = Straight path
```

Practice combining your controller inputs, and soon diagonal movement will become natural!
