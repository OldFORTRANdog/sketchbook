/*
 * Robotics with the BOE Shield - LeftServoTest
 * Left servo turns clockwise three seconds, stops 1 second, then
 * counterclockwise three seconds.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                            // Declare Left servo
 
void setup()                                 // Built in initialization block
{
  tone(4,3000,1000);
  delay(1000);
  servoLeft.attach(12);                     // Attach Left signal to pin 12

  servoLeft.writeMicroseconds(1300);        // Left wheel clockwise
  delay(3000);                               // ...for 3 seconds
 
  servoLeft.writeMicroseconds(1500);        // Stay still
  delay(1000);                               // ...for 3 seconds

  servoLeft.writeMicroseconds(1700);        // Left wheel counterclockwise
  delay(3000);                               // ...for 3 seconds
 
  servoLeft.writeMicroseconds(1500);        // Left wheel counterclockwise

}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}
