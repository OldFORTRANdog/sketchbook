/* 
   This is a test sketch for Holonomiic-X drive BreadBoardBOt (BBbot) based on 
   Adafruit assembled Motor Shield for Arduino v2
   Dave Eslinger 
   For use with the Adafruit Motor Shield v2 
   ---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

// declare R/C pins and variables
#define RC1 4 // Use precompiler statements to define pins; they are constants
#define RC2 8

int ch1; // Right Joysteck, Left - Right reading
int ch2; // Right Joysteck, Front - Back reading
//int ch3; // Left Joysteck, Front - Back reading
//int ch4; // Left Joystick, Left - Right reading
//int ch5; // VR(A)
//int ch6; // VR(B)

//float theta;
//float magnitude;
//float vx, vy;
//float w1, w2, w3, w4;
//byte w1_speed, w2_speed, w3_speed, w4_speed;
//byte w1_Dir, w2_Dir, w3_Dir, w4_Dir;
//const float sinCos45 = cos(45.0)
int xLow, xHigh, yLow,  yHigh;

boolean calRC_XY(int xLo, int xHi, int yLo, int yHi) {
  // This function reads joystick for 5 seconds and finds 
  // max/min values in x and y directions.
  xLo = xLo = 5000;
  xHi = yHi = -5000;

  // Define input pins for R/C 
  //  pinMode(RC1, INPUT);
  //  pinMode(RC2, INPUT);
  
  for (int i = 0; i < 500; i++ ) {
    // Read values
    ch1 = pulseIn(RC1, HIGH, 25000); //DLE changed 4 to RC1
    ch2 = pulseIn(RC2, HIGH, 25000); //DLE changed 8 to RC2
    if (ch1 < xLo) {
      xLo = ch1;
      Serial.println("New xLo");
    }
    if (ch1 > xHi) {
      xHi = ch1;
      Serial.println("New xHi");
    }
    if (ch2 < yLo) {
      yLo = ch2;
      Serial.println("New yLo");
    }
    if (ch2 > yHi) {
      yHi = ch2;
      Serial.println("New yHi");
    }
    delay(10);
  }
  return true;
}

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("X-Holonomic R/C drive Test");


  // Define input pins for R/C 
  pinMode(RC1, INPUT);
  pinMode(RC2, INPUT);
  
  if (calRC_XY(xLow, xHigh, yLow,  yHigh)) {
      Serial.print("xLo, xHi, yLo, yHi = ");
      Serial.print(xLow);
      Serial.print(", ");
      Serial.print(xHigh);
      Serial.print(", ");
      Serial.print(yLow);
      Serial.print(", ");
      Serial.println(yHigh);
      while(1) {
      }
    }

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Turn off all motors
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}

void loop() {
  //STEP 1: Read in the RC values
  ch1 = pulseIn(RC1, HIGH, 25000); //DLE changed 4 to RC1
  ch2 = pulseIn(RC2, HIGH, 25000); //DLE changed 8 to RC2

  ch1 = map(ch1,1450,2420,-100,100); // X value, mapped -100 to 100
  ch2 = map(ch2,1450,2400,-100,100); // Y value, mapped -100 to 100

  //STEP 2. Convert them to a direction vector centered at 0 straight ahead
  // i.e., not like a unit circle!
  float theta = atan2(ch1, ch2);
  float magnitude = sqrt((ch1*ch1) + (ch2*ch2) );

  //Serial.print("ch1: ");
  //Serial.print(ch1);
  //Serial.print(" ch2: ");
  //Serial.print(ch2);

  //Serial.print(" Ang: ");
  //Serial.print(degrees(theta));

  //Serial.print(" Mag: ");
  //Serial.print(magnitude);

  // magnitudes less than about 8 are neutral stick positions
  // and should probably just be ignored
  if(magnitude > 8.0f) {  

    float vx = magnitude * sin(theta);
    float vy = magnitude * cos(theta);
    //STEP 3. Find wheel vectors
    /* w1 = -vx;                   // v dot [-1, 0] / 25mm */
    /* w2 = 0.5*vx - sqrt3o2 * vy; // v dot [1/2, -sqrt(3)/2] / 25mm */
    /* w3 = 0.5*vx + sqrt3o2 * vy; // v dot [1/2, +sqrt(3)/2] / 25mm */
    /* w4 = 0.5*vx + sqrt3o2 * vy; // v dot [1/2, +sqrt(3)/2] / 25mm */

    // remember cos(-theta)=cos theta; sin(-theta) = -sin(theta)
    /* w1 = ( vx+vy)*sinCos45; // vx*cos(-45) + vy*sin(45)  */
    /* w2 = ( vx+vy)*sinCos45; // vx*cos( 45) + vy*sin(45)  */
    /* w3 = (-vx+vy)*sinCos45; // vx*cos( 45) + vy*sin(45)  */
    /* w4 = (-vx+vy)*sinCos45; // vx*cos(-45) + vy*sin(45)  */

    float w1 = vx*sin(-45) + vy*cos(-45); // vx*cos(-45) + vy*sin(45) 
    float w3 = vx*sin(-45) + vy*cos(-45); // vx*cos(-45) + vy*sin(45) 
    float w4 = vx*sin( 45) + vy*cos( 45); // vx*cos( 45) + vy*sin(45) 
    float w2 = vx*sin( 45) + vy*cos( 45); // vx*cos( 45) + vy*sin(45) 

    byte w1_Dir, w2_Dir, w3_Dir, w4_Dir;
    if ( w1 < 0 ) {
      w1_Dir = BACKWARD;
    }
    else {
      w1_Dir = FORWARD;
    }
 
    if ( w2 < 0 ) {
      w2_Dir = BACKWARD;
    }
    else {
      w2_Dir = FORWARD;
    }
 
    if ( w3 < 0 ) {
      w3_Dir = BACKWARD;
    }
    else {
      w3_Dir = FORWARD;
    }
 
    if ( w4 < 0 ) {
      w4_Dir = BACKWARD;
    }
    else {
      w4_Dir = FORWARD;
    }
 
    byte w1_speed = (byte) map(abs(w1), 0, 100, 0, 254);
    byte w2_speed = (byte) map(abs(w2), 0, 100, 0, 255);
    byte w3_speed = (byte) map(abs(w3), 0, 100, 0, 255);
    byte w4_speed = (byte) map(abs(w4), 0, 100, 0, 255);
  
    Serial.print("ch1: ");
    Serial.print(ch1);
    Serial.print(" ch2: ");
    Serial.print(ch2);

    Serial.print(" Ang: ");
    Serial.print(degrees(theta));

    Serial.print(" Mag: ");
    Serial.print(magnitude);


    Serial.print(" vx: ");
    Serial.print(vx);
    Serial.print(" vy: ");
    Serial.print(vy);

    Serial.print(" w1 & w3 speed & uncal.: ");
    Serial.print(w1_speed);
    Serial.print(", ");
    Serial.print(w1);
    Serial.print(" w2 & w4 speed & uncal.: ");
    Serial.print(w2_speed);
    Serial.print(", ");
    Serial.print(w2);
    //    Serial.print(" w3: ");
    //    Serial.print(w3_speed);
    //    Serial.print(", ");
    //Serial.print(w3);
//    Serial.print(" w4: ");
//    Serial.print(w4_speed);
//    Serial.print(", ");
//    Serial.print(w4);
    Serial.println();
    //    delay(10);

    motor1->run(w1_Dir);
    motor2->run(w2_Dir);
    motor3->run(w3_Dir);
    motor4->run(w4_Dir);

    motor1->setSpeed(w1_speed);  
    motor2->setSpeed(w2_speed);  
    motor3->setSpeed(w3_speed);  
    motor4->setSpeed(w4_speed);  
    delay(1000);
  }
  else { 
    //Serial.println();
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    motor3->run(RELEASE);
    motor4->run(RELEASE);   
    delay(10);
  }
}



