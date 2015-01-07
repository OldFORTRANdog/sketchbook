/* BOE SHiel - LeftServoClockwise
*/

#include <Servo.h>
Servo servoLeft;

void setup(){
  servoLeft.attach(13);
  servoLeft.writeMicroseconds(1300);
}

void loop() {
}
