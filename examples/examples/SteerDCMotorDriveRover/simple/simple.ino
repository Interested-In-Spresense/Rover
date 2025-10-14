#include "Rover.h"

// 駆動: ch0 (e0,p0) / ステア: ch1 (e1,p1)
SteerDCMotorDriveRover rover;

void setup() {
  // true = EN/PHモード
  // e0, p0, e1, p1, modePin(optional)
  rover.begin(true, 3, 4, 5, 6, 7);  // MODEピンあり
  // rover.begin(true, 3, 4, 5, 6);  // MODEピンなし

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
