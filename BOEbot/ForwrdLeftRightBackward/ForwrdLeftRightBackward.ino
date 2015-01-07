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
  
   // Full speed forward
  servoLeft.writeMicroseconds(1700);   //Left goes counter clockwise
  servoRight.writeMicroseconds(1300);   //Right goes clockwise
  delay(2000);

 // Spin LEFT
  servoLeft.writeMicroseconds(1300);   //Left goes clockwise
  servoRight.writeMicroseconds(1300);   //Right goes clockwise
  delay(600);
// Spin Right
  servoLeft.writeMicroseconds(1700);   //Left goes counter clockwise
  servoRight.writeMicroseconds(1700);   //Right goes counterclockwise
  delay(600);

  // Full speed backward
  servoLeft.writeMicroseconds(1300);   //Left goes counter clockwise
  servoRight.writeMicroseconds(1700);   //Right goes clockwise
  delay(2000);
  
   servoLeft.detach();
  servoRight.detach();
}

void loop () {
}    
 

