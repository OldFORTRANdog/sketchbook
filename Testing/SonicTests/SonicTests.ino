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

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
const byte SONIC_TRIGGER_PIN = 51;
const byte SONIC_ECHO_PIN = 50;

// Sonic sensor
const float TARGET_DISTANCE_INCHES = 10; 
const int MAX_SONIC_DISTANCE = 500;      // cm, optional, 500 cm is default

/* Define new untrasonic sensor with trigger & echo pins and 
   the maximum distance to be sensed. */
NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE); 

/* Define servo pins */
const byte PANSERVOPIN = 10; // Servo 1 on AdaFruit Motor Shield
const byte TILTSERVOPIN = 9; // Servo 2

float pingDist; // define variable to use for distance measurements

  
void setup(void){

  panServo.attach(PANSERVOPIN);
  tiltServo.attach(TILTSERVOPIN);
  panServo.write(90);
  tiltServo.write(90);
  
  Serial.begin(9600);  //Begin serial communcation
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit, 
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN,INPUT_PULLUP);

  pinMode(SONIC_TRIGGER_PIN,OUTPUT);
  pinMode(SONIC_ECHO_PIN,INPUT);
//  delay(2000);  // Two second delay to get the robot placed
}

void loop(){

  // Test some of the sonic library functions:  
  Serial.print(sonic.ping_in());
  Serial.print(" inches, cm = ");
  Serial.print(sonic.ping_cm());
  Serial.print(", actual ping time (ms) = ");
  int ping_milli = sonic.ping_median();
  Serial.print(ping_milli);
  Serial.print(", real inches = ");
  Serial.print(Distance_inches(ping_milli));
  Serial.print(", real cm = ");
  Serial.println(Distance_cm(ping_milli));
  delay(100); // Just to slow things down

}

/* float Distance_inches(int ping) { */
/*   float inches_per_sec = 13582.67;  // Equivilent to 345 m/s */
/*   return ping * inches_per_sec * 1e-6 *0.5; */
/* } */

/* float Distance_cm(int ping) { */
/*   float cm_per_sec = 34500.;        // Equivilent to 345 m/s */
/*   return ping * cm_per_sec * 1e-6 *0.5; */
/* } */
