// BOE SHield -- Forward3Seconds
// Go forward 3 seconds, then stop
#include <Servo.h>

Servo servoLeft; 
Servo servoRight;

void setup() {
  tone(4, 3000, 1000); // Play start tone for 1 second
  delay(1000);    // Wait for tone to end
  
  servoLeft.attach(12);      // Left on pin 12
  servoRight.attach(11);     // Right on pin 11
  
  // Full speed forward
  servoLeft.writeMicroseconds(1700);   //Left goes counter clockwise
  servoRight.writeMicroseconds(1300);   //Right goes clockwise
  delay(1500);
  
  servoLeft.detach();
  servoRight.detach();
}

void loop () {
}    
  
