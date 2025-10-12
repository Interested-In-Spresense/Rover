#include "Rover.h"

/* 左右駆動モータ：ch0 = 左, ch1 = 右 */
DualDCMotorRover rover(true, 3, 4, 5, 6);  

void setup() {
  rover.begin();
  rover.setSpeed(80);  /* 0～100 */
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
