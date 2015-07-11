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
const byte CH2_PIN = 26;
//const byte CH3_PIN = 27; // Left Joysteck, Front - Back reading
//const byte CH4_PIN = 7; // Left Joystick, Left - Right reading
//const byte CH5_PIN = 6; // VR(A)
//const byte CH6_PIN = 5; // VR(B)

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
//const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
//Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

// Define global variables
float direction;       // Velocity Vector Angle (DEGREES) from forward to drive
float magnitude;       // Magnitude (0-100) of movement vector in given direction
float duration;        // Duration to drive at given velocity vector
byte motorLeftdir;     // Clockwise or Counter clockwise for the 3 wheels
//byte motorBackdir;
byte motorRightdir;
int rightPower, leftPower;

//RC variables
int ch1; // Right Joystick channel, Left - Right reading
int ch2; // Right Joystick channel, Front - Back reading
//int ch3; // Left Joysteck, Front - Back reading
//int ch4; // Left Joystick, Left - Right reading
//int ch5; // VR(A)
//int ch6; // VR(B)

int turn;
int throttle;
int t2sign;
int inside;

void setup(void) {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
//  motorBack->run(RELEASE);
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
//  ch3 = pulseIn(CH3_PIN, HIGH); // Read the pulse width of 
//  ch4 = pulseIn(CH4_PIN, HIGH); // each channel
//  ch5 = pulseIn(CH5_PIN, HIGH); // Read the pulse width of 
//  ch6 = pulseIn(CH6_PIN, HIGH); // each channel
//  float xVector = map(ch1,1150,1800,-100,100);
//  float rightPower = map(ch2,1150,1800,-100,100);
//  float leftPower = map(ch3,1150,1800,-100,100);
//  float yVector = map(ch4,1150,1800,-100,100);
  throttle = map(ch2,1150,1800,-200,200);
  throttle = constrain(throttle, -200,200);
  turn = map(ch1,1150,1800,-200,200); 
  //turn = constrain(turn, -255, 255);
  t2sign = abs(float(turn) * float(throttle))/(float(turn) *float(throttle)); // Use to find the sign of the product
  inside = throttle - (t2sign * turn); 
  Serial.print(ch1);
  Serial.print(" = ch1, ch2 = ");
  Serial.println (ch2);
  if (turn >= 0) { // Right Turn, so left motor at full Throttle setting, right motor reduced by turn
    rightPower = 1500 + inside;
    leftPower = 1500 + throttle;
  }
  else { // Left Turn, so right motor at full Throttle setting, left motor reduced by turn
    rightPower = 1500 + throttle; 
    leftPower = 1500 + inside ;
  }
 
  duration = 10;

      // Find the actual motor speeds, 0-255, needed.  N.B. still need motor direction!
      //byte backSpeed  = map(abs(backPower),  0, 100, 0, 255);
      byte leftSpeed  = map(abs(leftPower),  0, 100, 0, 255);
      byte rightSpeed = map(abs(rightPower), 0, 100, 0, 255);

      // Set the speeds
      motorLeft-> setSpeed(leftSpeed);
      motorRight->setSpeed(rightSpeed);

      /* Set Motor directions.  For Adafruit V2 Motorshield:
           1 is Clockwise (Positive motor direction, FORWARD)
           2 is Counterclockwise (Negative vector direction, BACKWARD)
           3 is Brake (Doesn't work at present)
           4 is Release = stop power, not driving, but not brake

         We can use a trinary operator to set direction within run call
      */
      motorLeft-> run((leftPower  > 0) ? FORWARD: BACKWARD  );
      motorRight->run((rightPower > 0) ? FORWARD : BACKWARD );

      //Print out motor control details
      Serial.print("Speeds Back,Left,Right = ");
//      Serial.print(copysign(backPower, backSpeed));
      Serial.print(", ");
      Serial.print(copysign(leftPower, leftSpeed));
      Serial.print(", ");
      Serial.println(copysign(rightPower, rightSpeed));

      // Run motors for the duration needed, converting from seconds to milliseconds
      delay(duration);

}

