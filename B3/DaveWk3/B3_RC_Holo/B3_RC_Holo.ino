/* B3_RC_Holo.ino
   This is a test sketch for RADIO CONTROL driving mode of
   the three-wheeled drive Bread Board Bot (BBbot, B^3)

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

    Adapted from DLE's programs: B3_10_Holosquare and RC_ArcadeBOE 

   Programmer: Dave Eslinger; 7/10/2015
   Revisions: 
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define Constants
const float cos30sin60 = sqrt(3.0) / 2.0; // cos(30 deg) = sin(60 deg), need for wheel
                                          // vector calcs.

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
// declare R/C pins 
const byte CH1_PIN = 10;
const byte CH2_PIN = 9;

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

// Define global variables
float direction;       // Velocity Vector Angle (DEGREES) from forward to drive
float magnitude;       // Magnitude (0-100) of movement vector in given direction
float duration;        // Duration to drive at given velocity vector
byte motorLeftdir;     // Clockwise or Counter clockwise for the 3 wheels
byte motorBackdir;
byte motorRightdir;

//RC variables
int ch1; // Right Joystick channel, Left - Right reading
int ch2; // Right Joystick channel, Front - Back reading
int turn;
int throttle;
int t2sign;

void setup(void) {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);

  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit,
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  while (digitalRead(RIGHT_BUMP_PIN)) {}// Pause until right bump switch triggered
  delay(1000);                          // and 1 second to get hands out of the way
}
void loop(void) {
  ch1 = pulseIn(CH1_PIN, HIGH); // Read the pulse width of 
  ch2 = pulseIn(CH2_PIN, HIGH); // each channel
  float xVector = map(ch1,1150,1800,-100,100);
  float yVector = map(ch2,1150,1800,-100,100);
  Serial.print(ch1);
  Serial.print(" = ch1, ch2 = ");
  Serial.print (ch2);
  Serial.print("; X, Y = ");
  Serial.print(xVector);
  Serial.print(", ");
  Serial.print(yVector);
  throttle = sqrt(xVector*xVector + yVector*yVector);
  turn = atan2(yVector,xVector); 
 // turn = constrain(turn, -200, 200);
 // t2sign = abs(float(turn) * float(throttle))/(float(turn) *float(throttle)); // Use to find the sign of the product
 // Section for taking commands from Serial Input
 
  duration = 10;
  magnitude = throttle;
  direction = turn;
  
//  /* Autonomous loop for driving in a square */
//  for ( byte leg = 1; leg < 6; leg++ ) {   // Loop 5 times for a square, why?
//    duration = 2;                          // Constants per leg: Two seconds/leg
//    magnitude = 50;                        //                    50% max power
//    bool brake = false;                    //                    No braking
//    switch (leg) {
//      case 1: // Move forward
//        direction = 0.;
//        break;
//      case 2: // Move right
//        direction = 90.;
//        break;
//      case 3: // Move backward
//        direction = 180.;
//        break;
//      case 4: // Move left
//        direction = -90.;
//        break;
//      default: // Stop and pause for 4 seconds at starting point
//        magnitude = 0;
//        duration = 4;
//        direction = 0;
//        brake = 1; // hard stop
//    }

      Serial.print("direction = ");
      Serial.print(direction);
      Serial.print(", magnitude = ");
      Serial.print(magnitude);
      Serial.print(" and duration = ");
      Serial.println(duration);

      Serial.print("xVector, yVector = ");
      Serial.print(xVector);
      Serial.print(", ");
      Serial.println(yVector);

      /* Find relative power needed for each wheel based on the target 
      velocity vector.  Note that if the robot is not set up perfectly, there
      may be a need to multiply the backPower value by a fudge factor to prevent
      rotation of the robot. */
      float backPower = -xVector * 1.0;  // Change 1.0 for fudge factor
      float leftPower = 0.5 * xVector - cos30sin60 * yVector;  // rotation if needed
      float rightPower = 0.5 * xVector + cos30sin60 * yVector;

      // Find the actual motor speeds, 0-255, needed.  N.B. still need motor direction!
      byte backSpeed  = map(abs(backPower),  0, 100, 0, 255);
      byte leftSpeed  = map(abs(leftPower),  0, 100, 0, 255);
      byte rightSpeed = map(abs(rightPower), 0, 100, 0, 255);

      // Set the speeds
      motorBack-> setSpeed(backSpeed);
      motorLeft-> setSpeed(leftSpeed);
      motorRight->setSpeed(rightSpeed);

      /* Set Motor directions.  For Adafruit V2 Motorshield:
           1 is Clockwise (Positive motor direction, FORWARD)
           2 is Counterclockwise (Negative vector direction, BACKWARD)
           3 is Brake (Doesn't work at present)
           4 is Release = stop power, not driving, but not brake

         We can use a trinary operator to set direction within run call
      */
      motorBack-> run((backPower  > 0) ? FORWARD : BACKWARD );
      motorLeft-> run((leftPower  > 0) ? BACKWARD: FORWARD  );
      motorRight->run((rightPower > 0) ? FORWARD : BACKWARD );

      //Print out motor control details
      Serial.print("Speeds Back,Left,Right = ");
      Serial.print(copysign(backPower, backSpeed));
      Serial.print(", ");
      Serial.print(copysign(leftPower, leftSpeed));
      Serial.print(", ");
      Serial.println(copysign(rightPower, rightSpeed));

      // Run motors for the duration needed, converting from seconds to milliseconds
      delay(duration);

}
/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
/* void serialEvent() { */
/*   while (Serial.available()) { */
/*     // get the new byte: */
/*     char inChar = (char)Serial.read();  */
/*     // add it to the inputString: */
/*     inputString += inChar; */
/*     // if the incoming character is a neleftPowerine, set a flag */
/*     // so the main loop can do something about it: */
/*     if (inChar == '\n') { */
/*       stringComplete = true; */
/*     }  */
/*   } */
/* } */
