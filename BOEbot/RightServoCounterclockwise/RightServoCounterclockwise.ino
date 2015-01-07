/* BOE SHiel - LeftServoClockwise
*/

#include <Servo.h>
Servo servoRight;

void setup(){
  servoRight.attach(12);
  servoRight.writeMicroseconds(1700);
}

void loop() {
}
