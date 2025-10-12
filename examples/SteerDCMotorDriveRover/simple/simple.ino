#include "Rover.h"

// ch0: 駆動モータ, ch1: ステアリングモータ
SteerDCMotorDriveRover rover(true, 3, 4, 5, 6);

void setup() {
  rover.begin();
  rover.setSpeed(80);
}

void loop() {
  rover.front();
  delay(1000);

  rover.right();
  delay(500);

  rover.left();
  delay(500);

  rover.back();
  delay(1000);

  rover.stop();
  delay(1000);
}
