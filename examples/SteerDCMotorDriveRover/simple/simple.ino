/*
 *  SteerDCMotorDriveRover Sample
 *
 *  This example demonstrates basic movement of a rover
 *  using a DC motor for driving and another DC motor for steering.
 *
 *  Channel assignment:
 *    - ch0 : Drive motor (forward / backward)
 *    - ch1 : Steering motor (left / right)
 *
 *  Motion sequence:
 *    - Forward + steering
 *    - Backward + steering
 *    - Stop
 *
 *  Author: Interested-In-Spresense
 *  License: MIT
 */

#include "Rover.h"

// ch0: drive motor, ch1: steering motor
SteerDCMotorDriveRover rover;

void setup() {
  // MODE pin not used in this example
  rover.begin(true, 3, 4, 5, 6);
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
  rover.right();
  delay(500);
  rover.left();
  delay(500);

  rover.stop();
  delay(1000);

}
