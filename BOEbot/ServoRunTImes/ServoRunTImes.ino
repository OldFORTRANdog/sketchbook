// BOE shield - ServoOppositeDirections

#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(11);
  servoRight.attach(12);
  
  servoLeft.writeMicroseconds(1300); // clockwise
  servoRight.writeMicroseconds(1300); // clockwise
  delay(3000);
  servoLeft.writeMicroseconds(1700); // cntr-clockwise
  servoRight.writeMicroseconds(1700); // cntr-clockwise
  delay(3000);
  servoLeft.writeMicroseconds(1500); // stop
  servoRight.writeMicroseconds(1500); // stop
}
void loop () {
}

 
