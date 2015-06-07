/* BOE SHiel - LeftServoClockwise
 */

#include <Servo.h>
Servo servoLeft;

void setup(){
  servoLeft.attach(13);
}

void loop() {
  for (int ispeed = 1300; ispeed <= 1700; ispeed += 50) {
    servoLeft.writeMicroseconds(ispeed);
    delay(1000);
  }

  while (true){
    servoLeft.writeMicroseconds(1500);
  }
}


