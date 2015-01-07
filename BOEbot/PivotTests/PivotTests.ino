// BOE Shield Foreward,LeftReverseBackward
//
#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  tone(4,3000, 1000); //start tone
  delay(1000);

  servoLeft.attach(12);
  servoRight.attach(11);

  // Pivot forward-left
  servoLeft.writeMicroseconds(1500);   // Left wheel stop
  servoRight.writeMicroseconds(1300);  // Right wheel clockwise
  delay(600);

  // Pivot forward-right
  servoLeft.writeMicroseconds(1700);   // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500);  // Right wheel stop
  delay(600);

  // Pivot backward-left
  servoLeft.writeMicroseconds(1500);   // Left wheel stop
  servoRight.writeMicroseconds(1700);  // Right wheel counterclockwise
  delay(600);

  // Pivot backward-right
  servoLeft.writeMicroseconds(1300);     // Left wheel clockwise
  servoRight.writeMicroseconds(1500);    // Right wheel stop
  delay(600);

  servoLeft.detach();
  servoRight.detach();
}

void loop () {
}    



