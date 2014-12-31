/* AdaAutoDemo.ino
 This is a test sketch for autonomous driving mode of
 the three-wheeled drive Bread Board Bot (BBbot, B^3) 
 
 Arduino: Arduino Mega v3
 Motor Shield: Adafruit assembled Motor Shield for Arduino v2
 ---->  http://www.adafruit.com/products/1438
 
 Programmer: Dave Eslinger; December 2, 2014
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
//#include <"utility/Adafruit_PWMServoDriver.h"
#include <math.h>
#include <Servo.h>

#define LBUMPPIN 3
//#define FBUMPPIN 5
#define RBUMPPIN 4

#define ANYFOBPIN 2
#define AFOBPIN 5
#define BFOBPIN 6
#define CFOBPIN 7
#define DFOBPIN 8
/* #define AFOBPIN 37 */
/* #define BFOBPIN 35 */
/* #define CFOBPIN 33 */
/* #define DFOBPIN 31 */

#define TILTSERVOPIN 9
#define PANSERVOPIN 10

float theta;
int direction;
float magnitude;
float duration;
byte brake;
byte mLdir;
byte mFdir;
byte mRdir;

byte pan;
byte tilt;

unsigned long timer;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define 'ports' M1, M2, M3 or M4 for motors.
Adafruit_DCMotor *mL = AFMS.getMotor(1);
Adafruit_DCMotor *mF = AFMS.getMotor(2);
Adafruit_DCMotor *mR = AFMS.getMotor(3);

Servo panServo;
Servo tiltServo;

void setup(void){
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  mL->run(RELEASE);
  mF->run(RELEASE);
  mR->run(RELEASE);
  // Bump Switch pins
  pinMode(LBUMPPIN,INPUT_PULLUP);
  pinMode(RBUMPPIN,INPUT_PULLUP);

  // Keyfob Remote pins
  //  pinMode(ANYFOBPIN, INPUT); // DOES NOT HAVE 330 ohm pulldown resistor on it
  pinMode(AFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
  pinMode(AFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
  pinMode(AFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
  pinMode(AFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it

  /* // Servo pins */
  /* panServo.attach(PANSERVOPIN); */
  /* tiltServo.attach(TILTSERVOPIN); */
}

void loop(void){
  byte lBump = digitalRead(LBUMPPIN);
  byte rBump = digitalRead(RBUMPPIN);
  /* Serial.print("lBump = "); */
  /* Serial.print(lBump); */
  /* Serial.print(", rBump = "); */
  /* Serial.print(rBump); */
 
  //duration = 3; // check for key fob press every 3 ms
  duration = 50; // check for key fob press every 50 ms
  timer = millis();
 
  Serial.print(digitalRead(ANYFOBPIN));
  Serial.print(digitalRead(AFOBPIN));
  Serial.print(digitalRead(BFOBPIN));
  Serial.print(digitalRead(CFOBPIN));
  Serial.println(digitalRead(DFOBPIN));

  if ( digitalRead(AFOBPIN) ) {
    direction = 0;
    magnitude = 100;
 }
  else  if ( digitalRead(BFOBPIN) ) {
    direction = 90;
    magnitude = 100;
  }
  else if ( digitalRead(CFOBPIN) ) {
    direction = 270;
    magnitude = 100;
  }
  else if ( digitalRead(DFOBPIN) ) {
    direction = 180;
    magnitude = 100;
  }
  /* else { */
  /*   direction = 0; */
  /*   duration = 0; */
  /* } */

  //magnitude = 0;
  
  /* panServo.write(pan); */
  /* tiltServo.write(tilt); */
  
  /* if ( lBump and rBump ) { // No switch, drive according to Fob */
  /*   duration = 100; */
  /*   magnitude = 75; */
  /*   //  direction = 0.; */
  /* } */
  /* else */
  /* if (not lBump ) {   // Left switch triggered, move right */
  /*   duration = 100; */
  /*   magnitude = 75; */
  /*   direction = 90.; */
  /*   Serial.println("Left Bump"); */
  /* }     */
  /* else {                   // Right switch triggered, move left */
  /*   duration = 100; */
  /*   magnitude = 75; */
  /*   direction = -90.; */
  /*   Serial.println("Right Bump"); */
  /* } */

  theta = ( M_PI * direction ) / 180. ; 
  if( duration > 0 ) {

    float vx = magnitude * sin(theta);
    float vy = magnitude * cos(theta);
    /* Serial.print("vx, vy = "); */
    /* Serial.print(vx); */
    /* Serial.print(", "); */
    /* Serial.println(vy); */

    const float sqrt3o2 = 1.0*sqrt(3)/2;
    //STEP 3. Find wheel vectors
    float wF = -vx * .95 ;  // Multiply by fudge factor to prevent rotation if needed
    float wL = 0.5*vx - sqrt3o2 * vy; 
    float wR = 0.5*vx + sqrt3o2 * vy; 

    byte wF_speed = (byte) map(abs(wF), 0, 100, 0, 255);
    byte wL_speed = (byte) map(abs(wL), 0, 100, 0, 255);
    byte wR_speed = (byte) map(abs(wR), 0, 100, 0, 255);
    /* Set Motor directions.  For Adafruit V2 Motorshield: 
     1 is Clockwise (Positive motor direction)
     2 is Counterclockwise (Negative vector direction)
     	 3 is Brake (May not work)
     	 4 is Release = stop power, not driving, but not brake
     	 so we can use a logic test since TRUE = 1 and FALSE = 0
     */
    mF->run((wF > 0) ? 1: 2 );
    mL->run((wL > 0) ? 1: 2 );
    mR->run((wR > 0) ? 1: 2 );


    // Set the speeds
    mF->setSpeed(wF_speed);
    mL->setSpeed(wL_speed);
    mR->setSpeed(wR_speed);

    //Print out motor control details
    /* Serial.print("Speeds F,L,R = "); */
    /* Serial.print(copysign(wF_speed,wF)); */
    /* Serial.print(", "); */
    /* Serial.print(copysign(wL,wL_speed)); */
    /* Serial.print(", "); */
    /* Serial.println(copysign(wR,wR_speed)); */

    // Run motors for the duration requested
    //        delay(duration); 
    // replace with timer & millis test in duration if statment
    

  }
  /* else{ // no duration entered, so stop all motors */
  /*   mF->setSpeed(0); */
  /*   mL->setSpeed(0); */
  /*   mR->setSpeed(0); */
  /* }   */

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
/*     // if the incoming character is a newline, set a flag */
/*     // so the main loop can do something about it: */
/*     if (inChar == '\n') { */
/*       stringComplete = true; */
/*     }  */
/*   } */
/* } */

