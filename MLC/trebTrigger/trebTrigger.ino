/* trebTrigger
  Uses a keybob to trigger and reset a DC motor to pull the trebuchet trigger


 Motor Shield: Adafruit assembled Motor Shield for Arduino v2
 ---->  http://www.adafruit.com/products/1438
 
 Programmer: Dave Eslinger; 18 January, 2015
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
//#include <"utility/Adafruit_PWMServoDriver.h"
#include <math.h>

//#define BROWNFOB

#ifdef BROWNFOB 
#define AFOBPIN 5 // Chinese Fobs
#define BFOBPIN 3
#define CFOBPIN 6
#define DFOBPIN 4
#define ANYFOBPIN 7
#else
#define AFOBPIN 6 // AdaFruit Fob
#define BFOBPIN 5
#define CFOBPIN 4
#define DFOBPIN 3
#define ANYFOBPIN 7 
#endif

#define FIREPIN 12

/* unsigned long timeCheck; */
// unsigned long myTimer; 
unsigned long duration;
byte direction;
byte magnitude;

boolean armed;
boolean fired;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define motor port for motors.
Adafruit_DCMotor *mTrigger = AFMS.getMotor(4);

void setup(void){
  Serial.begin(9600);
  AFMS.begin();  // Motor controller objct
  mTrigger->run(RELEASE);   // Turn off the motor

  //   Keyfob Remote pins
     pinMode(AFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
     pinMode(BFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
     pinMode(CFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
     pinMode(DFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it
     pinMode(ANYFOBPIN, INPUT); // Has 330 ohm pulldown resistor on it

     digitalWrite(AFOBPIN,LOW);
     digitalWrite(BFOBPIN,LOW);
     digitalWrite(CFOBPIN,LOW);
     digitalWrite(DFOBPIN,LOW);
     digitalWrite(ANYFOBPIN,LOW);
       
     // set up Firing pin for testing
     pinMode(FIREPIN, OUTPUT);
     digitalWrite(FIREPIN, HIGH);
     armed = false;
     fired = false;
     /* armCode = String("AADDC"); */
     /* fireCode = String("ABC"); */
}

void loop(void) {
  //  timeCheck = 50; // check for key fob press every 50 ms
  //  myTimer = millis();
 
  Serial.print(digitalRead(ANYFOBPIN));
  Serial.print(digitalRead(AFOBPIN));
  Serial.print(digitalRead(BFOBPIN));
  Serial.print(digitalRead(CFOBPIN));
  Serial.println(digitalRead(DFOBPIN));

  /* if ( digitalRead(AFOBPIN) ) { */
  /*   direction = FORWARD; */
  /*   magnitude = 255; */
  /*   duration = 1000; */
  /* } */
  /* else  if ( digitalRead(BFOBPIN) ) { */
  /*   direction = BACKWARD; */
  /*   magnitude = 255; */
  /*   duration = 200; */
  /* } */
  /* else { */
  /*   direction = RELEASE; */
  /*   magnitude = 0; */
  /*   duration = 0; */
  /* } */

 /* // Set the speedRun the motor */
 /*  mTrigger->setSpeed(magnitude); */
 /*  mTrigger->run(direction); */
 /*  delay(duration); */

  //  if(codeEntered(armCode)) {
    digitalWrite(FIREPIN,LOW);
    delay(1000);
    digitalWrite(FIREPIN,HIGH);
    delay(1000);
    //  }
}

boolean codeEntered(secretCode) {
  long timeOut = 5000; // Millsec between button pushes before code resets
  long pressTime = millis();
  byte codePosition = 0;
  char entry;

  while (millis() - pressTime < timeOut) {
    // Read FOB buttons using a binary incoding
    byte fobValue = digitalRead(AFOBPIN) + // the 1's
      2 * digitalRead(BFOBPIN) +           // the 2's
      4 * digitalRead(CFOBPIN) +           // the 4's
      8 * digitalRead(DFOBPIN);            // the 8's
    
    switch (fobValue) {
    case(0):  // Nothing was pressed
      entry = "";
      break;
    case(1):  // Button A was pressed
      entry = "A";
      break;
    case(2):  // Button B was pressed
      entry = "B";
      break;
    case(3):  // Button C was pressed
      entry = "C";
      break;
    case(4):  // Button D was pressed
      entry = "D";
      break;
    default:
      entry = "";
    }
    Serial.print(entry);
    Serial.println(secretCode);
    if (entry != "") {       // there was a button pushed
	if (secretCode[codePosition] = entry) { // Correct code entered
	  codePosition++;
	  if (codePosition == len(secretCode)) { // All code entered correctly
	    return true;
	  }
	}
	else { // incorrect code
	  codePosition = 0;
	  Serial.println("ERROR! Entered code incorrect. Code reset \g");
	}
      pressTime = millis();
    }
  }
  codePosition = 0;  // Took too long
  Serial.println("Timeout: Entered code reset \g");
  return false;
}

