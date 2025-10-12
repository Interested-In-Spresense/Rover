# Rover Library

**Rover** is a simple Arduino library for controlling three types of rovers using the **DRV8835 motor driver** and **Servo**:

- `DualDCMotorRover`: Differential drive rover (2 DC motors)
- `SteerDCMotorDriveRover`: Rover with DC motor drive + DC motor steering
- `SteerServoDriveRover`: Rover with DC motor drive + Servo steering

---

## Features

- Control forward, backward, left, right, and stop
- Set speed (0–100%)
- For servo steering, set center and range
- Single DRV8835 instance to control 1 or 2 motors
- Easy to integrate into Arduino sketches

---

## Installation

1. Download this repository as ZIP or clone it:

```bash
git clone https://github.com/Interested-In-Spresense/Rover.git
```

2. Place the folder into your Arduino `libraries` directory.
3. Make sure dependencies are installed:
   - [Servo](https://www.arduino.cc/en/Reference/Servo)
   - [Drv8835](https://github.com/Interested-In-Spresense/Drv8835)

---

## Usage Examples

### 1. DualDCMotorRover

```cpp
#include "Rover.h"

DualDCMotorRover rover(true, 3, 4, 5, 6);

void setup() {
  rover.begin();
  rover.setSpeed(80);
}

void loop() {
  rover.front();
  delay(1000);
  rover.back();
  delay(1000);
  rover.left();
  delay(500);
  rover.right();
  delay(500);
  rover.stop();
  delay(1000);
}
```

### 2. SteerDCMotorDriveRover

```cpp
#include "Rover.h"

SteerDCMotorDriveRover rover(true, 3, 4, 5, 6);

void setup() {
  rover.begin();
  rover.setSpeed(80);
}

void loop() {
  rover.front();
  delay(1000);
  rover.back();
  delay(1000);
  rover.right();
  delay(500);
  rover.left();
  delay(500);
  rover.stop();
  delay(1000);
}
```

### 3. SteerServoDriveRover

```cpp
#include "Rover.h"

SteerServoDriveRover rover(true, 3, 4, 9); // Servo pin 9

void setup() {
  rover.begin();
  rover.setSpeed(80);
  rover.setSteerCenter(90);
  rover.setSteerRange(30);
}

void loop() {
  rover.front();
  delay(1000);
  rover.back();
  delay(1000);
  rover.right();
  delay(500);
  rover.left();
  delay(500);
  rover.stop();
  delay(1000);
}
```

---

## Servo Steering Adjustment

```cpp
rover.setSteerCenter(95); // Sets neutral position
rover.setSteerRange(25);  // Sets maximum left/right angle
```

---

## License

This library is licensed under the **MIT License**.

