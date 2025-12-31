# Quick Reference Card - Diagonal Movement

## 🎮 Controller Layout (Arcade Drive)

```
┌─────────────────────────────────┐
│     VEX V5 Controller           │
│                                 │
│   Left Stick      Right Stick   │
│       ↑                ←→       │
│      ←+→                        │
│       ↓                         │
│                                 │
│   Forward/Back     Turn L/R     │
└─────────────────────────────────┘
```

## 🚀 Quick Start

### Step 1: Wire Your Robot
- Left Front Motor → PORT1
- Left Back Motor → PORT2
- Right Front Motor → PORT3
- Right Back Motor → PORT4

### Step 2: Download Program
- Open in VEXcode V5
- Download to brain
- Run driver control

### Step 3: Drive!
- **Forward only**: Left stick forward
- **Turn only**: Right stick left/right
- **Diagonal**: Use BOTH sticks together!

## 📐 The Magic Formula

```
Left Motor  = Forward + Turn
Right Motor = Forward - Turn
```

## 🎯 Common Movements

| Movement | Left Stick | Right Stick | Result |
|----------|-----------|-------------|---------|
| Straight | 100% ↑ | 0% | → Straight forward |
| Rotate | 0% | 50% → | ↻ Spin right |
| **Diagonal ↗** | **80% ↑** | **40% →** | **Curve forward-right** |
| **Diagonal ↖** | **80% ↑** | **40% ←** | **Curve forward-left** |

## ⚙️ Configuration

Edit `src/robot-config.cpp`:

```cpp
// Adjust these values
const double DRIVE_DEADZONE = 5.0;     // 0-20
const double DRIVE_SENSITIVITY = 1.0;  // 0.1-2.0
```

## 🏁 Competition Tips

### Offense
```cpp
// Fast diagonal approach to goal
arcadeDrive(90, 40);
```

### Defense
```cpp
// Quick evasive diagonal
arcadeDrive(-70, 60);
```

### Skills Run
```cpp
// Precise diagonal positioning
arcadeDrive(50, 25);
```

## 🔧 Switch Drive Modes

Edit `src/main.cpp` → `usercontrol()`:

**Arcade Drive** (Default)
```cpp
arcadeDrive(forward, turn);
```

**Tank Drive**
```cpp
tankDrive(leftSide, rightSide);
```

**Field-Centric** (Mecanum)
```cpp
fieldCentricDrive(forward, strafe, turn);
```

## 🐛 Troubleshooting

| Problem | Solution |
|---------|----------|
| Robot turns when going straight | Reverse one motor direction |
| Too fast/sensitive | Lower DRIVE_SENSITIVITY |
| Controller drift | Increase DRIVE_DEADZONE |
| Diagonal not smooth | Check motor connections |

## 📚 More Info

- **README.md** - Full documentation
- **EXAMPLES.md** - Code examples
- **VISUAL_GUIDE.md** - Diagrams & math
- **CONFIGURATION.md** - Hardware setups

## 💡 Pro Tips

1. **Practice smooth inputs** - Don't jerk the sticks
2. **Anticipate turns** - Start turning before you think you need to
3. **Use both sticks** - That's where the magic happens!
4. **Start slow** - Begin at 50% speed, increase as you improve

---

**Made with ❤️ for VEX Robotics Teams**
