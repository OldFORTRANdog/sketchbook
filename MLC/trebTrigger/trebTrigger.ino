/* trebTrigger
  Uses a keybob to trigger and reset a DC motor to pull the trebuchet trigger


 Motor Shield: Adafruit assembled Motor Shield for Arduino v2
 ---->  http://www.adafruit.com/products/1438
 
 Programmer: Dave Eslinger; 18 January, 2015
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
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

boolean armed = false;
boolean fired = true;

String armCode = String("AADDC");
String fireCode = String("ABC");

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

  if(codeEntered(armCode)) {
    digitalWrite(FIREPIN,LOW);
    delay(1000);
    digitalWrite(FIREPIN,HIGH);
    delay(1000);
  }
}

boolean codeEntered(String secretCode) {
  unsigned long timeOut = 5000; // Millsec between button pushes before code resets
  unsigned long pressTime = millis();
  unsigned long debounce = 200;
  byte codePosition = 0;
  String entry;
  byte oldFob = 0;
  
  while (millis() - pressTime < timeOut) { // Not timed out
    // Read FOB buttons using a binary incoding
    /* byte fobValue = digitalRead(AFOBPIN) + // the 1's */
    /*   2 * digitalRead(BFOBPIN) +           // the 2's */
    /*   4 * digitalRead(CFOBPIN) +           // the 4's */
    /*   8 * digitalRead(DFOBPIN);            // the 8's */
    byte fobValue = readFob();
    if (fobValue > 0 &&  millis()-pressTime >=debounce)  { 
      // there was a button pushed after the debounce period
      pressTime = millis();
      switch (fobValue) {
      case(1):  // Button A was pressed
	entry = String('A');
	break;
      case(2):  // Button B was pressed
	entry = String('B');
	break;
      case(4):  // Button C was pressed
	entry = String('C');
	break;
      case(8):  // Button D was pressed
	entry = String('D');
	break;
      default:
	entry = String(' ');
      }
      Serial.print("entry = ");
      Serial.print(entry);
      Serial.print(", secretCode = ");
      Serial.print(secretCode);
      Serial.print(", fobValue = ");
      Serial.print(fobValue);
      Serial.print(", oldFob = ");
      Serial.println(oldFob);

      if (secretCode[codePosition] == entry[0]) { // Correct code entered
	codePosition++;
	if (codePosition == secretCode.length()) { // All code entered correctly
	  return true;
	}
      }
      else { // incorrect code
	codePosition = 0;
	Serial.println("ERROR! Entered code incorrect. Code reset \7");
	return false;
      }
      pressTime = millis();
      oldFob = fobValue;
      // Delay for debounce of Fob keys
    } // End of fobValue if block
  }
  codePosition = 0;  // Took too long
  Serial.println("Timeout: Entered code reset \7");
  return false;
}


byte readFob() {
  /*  Reads fob button pushes, waits until nothing 
      pushed to return a value  */
  byte checkFob = 0;
  byte buttonsUp = 15;
  //  while (checkFob = 0) {
    checkFob = digitalRead(AFOBPIN) + // the 1's
      2 * digitalRead(BFOBPIN) + // the 2's
      4 * digitalRead(CFOBPIN) + // the 4's
      8 * digitalRead(DFOBPIN);  // the 8's
    //  }
  // Serial.println(checkFob);
  /* while (buttonsUp > 0 ) { */
  /*   buttonsUp = digitalRead(AFOBPIN) + // the 1's */
  /*     2 * digitalRead(BFOBPIN) + // the 2's */
  /*     4 * digitalRead(CFOBPIN) + // the 4's */
  /*     8 * digitalRead(DFOBPIN);  // the 8's */
  /*   Serial.println(buttonsUp); */
  /* } */
  return checkFob;
}
