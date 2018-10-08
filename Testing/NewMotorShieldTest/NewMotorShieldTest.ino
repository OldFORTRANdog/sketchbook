/* B3_09_Servo_Sonic.ino

   Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
   forward.   When within 10 inches of something, turn servos to find clearest path
   and then go that way.
   When a whisker bump sensor on either side hits something,
   back up and turn slightly away from that direction and resume 
   forward path.  

   Stop at a specified distance from an object directly ahead.

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; June 13, 2015
   Revisions:   Added sonic sensors on servos, June 23, 2016.
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>
#include <NewPing.h>
#include <Servo.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Servos 
Servo panServo;
Servo tiltServo;

/* Define Constants */


// Define 'ports' for motors.
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

/* Define servo pins */
const byte PANSERVOPIN = 10; // Servo 1 on AdaFruit Motor Shield
const byte TILTSERVOPIN = 9; // Servo 2

float pingDist; // define variable to use for distance measurements

  
void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorRight->run(RELEASE);

  panServo.attach(PANSERVOPIN);
  tiltServo.attach(TILTSERVOPIN);
  panServo.write(90);
  tiltServo.write(90);
  
  Serial.begin(9600);  //Begin serial communcation
  
 }

void loop(){
     panServo.write(180);
     delay(1000);
     panServo.write(90);
     delay(1000);
     panServo.write(0);
      delay(1000);
     panServo.write(90);


}
