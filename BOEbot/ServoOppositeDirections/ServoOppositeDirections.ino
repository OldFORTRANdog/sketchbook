// BOE shield - ServoOppositeDirections

#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
  
  servoLeft.writeMicroseconds(1700); // counter clockwise
  servoRight.writeMicroseconds(1300); // clockwise
}
void loop () {
}

 
