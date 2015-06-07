/* B3_SpinSquare.ino
   Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
   in a square, stopping at (or near!) end point.

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; June 7, 2015
   Revisions: 
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants
const byte TESTSPEED = 155;
const byte DIRECTION = TURNLEFT;

// Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void){
  
  delay(1000); // Delay for a second to give time to place the robot.

  // Autonomous loop for driving in a square
  for ( byte leg = 1; leg <= 4; leg++ ) {
    drive(10., TESTSPEED, *motorLeft, *motorRight);// Forward for 10 inches
    spin(-90., TESTSPEED, *motorLeft, *motorRight); // 90 deg. to left
    allStop(FORWARD, *motorLeft, *motorRight);
    delay(500);  // Pause for 1/2 a second after turning
  }
  delay(3000);
  for ( byte leg = 1; leg <= 4; leg++ ) {
    drive(10., TESTSPEED, *motorLeft, *motorRight);// Forward for 10 inches
    spin(90., TESTSPEED, *motorLeft, *motorRight); // 90 deg. to left
    allStop(FORWARD, *motorLeft, *motorRight);
    delay(500);  // Pause for 1/2 a second after turning
  }
  while(1){}
}

/* void drive(float distance, byte speed, */
/* 	   Adafruit_DCMotor mLeft, Adafruit_DCMotor mRight) { */
/*   byte direction; */
/*   mLeft.setSpeed(speed);  // Set both speeds */
/*   mRight.setSpeed(speed); */

/*   if (distance > 0) {   // Postive distance is forward */
/*     direction = FORWARD; */
/*   } */
/*   else { */
/*     direction = BACKWARD; */
/*   } */
/*   float duration = duration_per_distance(distance, speed); */
/*   /\* Now move in the desired directions for that duration *\/ */
/*   mLeft.run(direction); */
/*   mRight.run(direction); */
/*   delay(duration); */
/*   allStop(direction, mLeft, mRight); */
/*   return; */
/* } */

/* void spin(float degrees, byte speed, */
/* 	    Adafruit_DCMotor mLeft, Adafruit_DCMotor mRight) { */
/*   /\* A spin turns moves the wheels in opposite directions.  Each */
/*      needs to go the same distance, which is determined by the */
/*      degrees parameter, around a circle with a diameter of the */
/*      robot track width. */

/*     The actual distance will be the Circumference * the fraction of the */
/*     circle needed, given by the ratio degrees/360. *\/ */
/*   // float distance = PI * trackWidth * degrees / 360.; */
/*   float distance = PI * trackWidth* degrees / 360.; */
/*   float duration = duration_per_distance(distance, speed); */
/*   if (degrees > 0) { */
/*     /\* Positive angle is spin turn to the right; therefore right motor goes */
/*        backwards and left side goes forward *\/ */
/*     mRight.run(BACKWARD); */
/*     mLeft.run(FORWARD); */
/*   } */
/*   else { // Negative or 0 angle, turn to the left */
/*     mRight.run(FORWARD); */
/*     mLeft.run(BACKWARD); */
/*   } */
/*   delay(duration); */
/*   return; */
/* } */

/* float duration_per_distance( float distance, byte speed) { */
/*   /\* Find drive time in milliseconds from relationship developed from */
/*      observations of distance/time for a speed.  *\/ */
/*   float duration = abs(distance) * 50.;  // 500 ms/distnace unit for testing */
/*   return duration; */
/* } */