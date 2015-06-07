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

#define ARMPIN 12
#define MOTORPIN 11
#define MOTPWMPIN 1

#define MPORT 4

/* unsigned long timeCheck; */
// unsigned long myTimer; 
unsigned long duration;
byte direction;
byte magnitude;

boolean armed = false;
boolean fired = true;

String armCode = String("ABC");
String fireCode = String("DC");

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define motor port for motors.
Adafruit_DCMotor *mTrigger = AFMS.getMotor(MPORT);

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
       
     // set up Firing pin for testing with 12V motor
     pinMode(MOTORPIN, OUTPUT);
     pinMode(ARMPIN, OUTPUT);
     digitalWrite(ARMPIN, HIGH);
     digitalWrite(MOTORPIN, LOW);
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

  /* for(byte val = 0; val<256; val++) { */
  /*   Serial.println(val); */
  /*   analogWrite(MOTORPIN, val); */
  /*   delay(1000); */
  /* } */


  if(codeEntered(armCode)) {
    armTreb();  // Do whatever is needed for arming
    // Armed, now check for the fire code
    if(codeEntered(fireCode)) {
      fireTreb();
    }
    else {
      digitalWrite(ARMPIN,HIGH); // ARMPIN off if correct code not entered
    }
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
 
    byte fobValue = readFob(); // Read the fob code
    if (fobValue > 0 &&  millis()-pressTime >=debounce)  { 
      // there was a button pushed after the debounce period
      // and before the timeout period
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
      Serial.print(", secretCode.length= ");
      Serial.print(secretCode.length());
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
	Serial.println("ERROR! Entered code incorrect. Entered code cleared.");
	return false;
      }
      pressTime = millis();
      oldFob = fobValue;
      // Delay for debounce of Fob keys
    } // End of fobValue if block
  }
  codePosition = 0;  // Took too long
  Serial.println("Timeout: Please start again.");
  //digitalWrite(ARMPIN,HIGH);
  return false;
}


byte readFob() {
  /*  Reads one fob button push, then waits until all buttons are
      released to return the initial button value  */
byte checkFob = 0;
byte buttonsUp = 15;
do {
  checkFob = digitalRead(AFOBPIN) + // the 1's
    2 * digitalRead(BFOBPIN) + // the 2's
    4 * digitalRead(CFOBPIN) + // the 4's
    8 * digitalRead(DFOBPIN);  // the 8's
  //  Serial.print(checkFob);
}  while (checkFob == 0);  
do {
  buttonsUp = digitalRead(AFOBPIN) + // the 1's
    2 * digitalRead(BFOBPIN) + // the 2's
    4 * digitalRead(CFOBPIN) + // the 4's
    8 * digitalRead(DFOBPIN);  // the 8's
  Serial.print(", buttonsUp = ");
  Serial.println(buttonsUp);
} while (buttonsUp > 0);
/* Serial.println(); */
/* Serial.print("Out of checkFob do/while loop, checkFob = "); */
/* Serial.println(checkFob); */
return checkFob;
}

void armTreb(void) {
  digitalWrite(ARMPIN,LOW);
}

void fireTreb(void) {
 // Set the speedRun the motor
  digitalWrite(ARMPIN,HIGH);
  Serial.println("BOOM, Trebuchet launched!");
  /* magnitude = 250; */
  /* direction = FORWARD; */
  duration = 5000; 
  /* mTrigger->setSpeed(magnitude); */
  /* mTrigger->run(direction); */
  /* mTrigger->run(RELEASE); */
  digitalWrite(MOTORPIN, HIGH);
  delay(duration);
  digitalWrite(MOTORPIN, LOW);
}
