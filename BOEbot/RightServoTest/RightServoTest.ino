/*
 * Robotics with the BOE Shield - RightServoTest
 * Right servo turns clockwise three seconds, stops 1 second, then
 * counterclockwise three seconds.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoRight;                            // Declare right servo
 
void setup()                                 // Built in initialization block
{
  tone(4,3000,1000);
  delay(1000);
  servoRight.attach(11);                     // Attach right signal to pin 12

  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(3000);                               // ...for 3 seconds
 
  servoRight.writeMicroseconds(1500);        // Stay still
  delay(1000);                               // ...for 3 seconds

  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(3000);                               // ...for 3 seconds
 
  servoRight.writeMicroseconds(1500);        // Right wheel counterclockwise

}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}
