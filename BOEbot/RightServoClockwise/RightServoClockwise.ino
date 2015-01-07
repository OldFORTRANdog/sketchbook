/* BOE SHiel - LeftServoClockwise
*/

#include <Servo.h>
Servo servoRight;

void setup(){
  servoRight.attach(12);
  servoRight.writeMicroseconds(1300);
}

void loop() {
}
