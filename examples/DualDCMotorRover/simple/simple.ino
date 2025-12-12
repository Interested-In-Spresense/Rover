/*
 *  DualDCMotorRover Sample
 *
 *  This example demonstrates basic movements of a differential-drive rover
 *  using the Rover library with a DRV8835 motor driver.
 *
 *  Motion sequence:
 *    - Forward + turn
 *    - Backward + turn
 *    - Stop + pivot turn
 *
 *  Hardware:
 *    - Dual DC motors (left / right)
 *    - DRV8835 motor driver
 *
 *  Author: Interested-In-Spresense
 *  License: MIT
 */
 
#include "Rover.h"

DualDCMotorRover rover;

void setup() {
  // with MODE pin
  rover.begin(true, 6, 12, 9, 13, 2);
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

  rover.right();
  delay(500);
  rover.left();
  delay(500);

}
