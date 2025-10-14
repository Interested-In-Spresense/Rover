#include "Rover.h"

DualDCMotorRover rover;

void setup() {
  // MODEピン付き
  rover.begin(true, 6, 12, 9, 13, 2);
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
