// BOE shield - RemoteHack
//
// Using a remote control board and controller from a R/C car toy.
// Removed stranded wires and resoldered solid wire to use with solderless breadboard.
// Trying pin config: 
// Label:   Wire  : BOE Shield : Desired Behaviour
//  +V      red   : Vin        
//  V-      black : Common
//  LM:    Yellow :   7        : Robot Right forward
//  RM:     blue  :   6        : Robot Right backward
//  FM:    Yellow :   5        : Robot LEFT forward
//  BM:     blue  :   4        : Robot LEFT backward
//#use Serial
#include <Servo.h>
Servo servoLeft;
Servo servoRight;


// declare R/C pins and variables
int pinLB = 5;
int pinLF = 4;
int pinRB = 6;
int pinRF = 7;
int valLB, valLF, valRB, valRF;

void setup() {
  Serial.begin(9600);
  servoLeft.attach(12);
  servoRight.attach(11);


  pinMode(pinLB, INPUT);
  digitalWrite(pinLB, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinLF, INPUT);
  digitalWrite(pinLF, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinRB, INPUT);
  digitalWrite(pinRB, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinRF, INPUT);
  digitalWrite(pinRF, HIGH); // pullup current unless signal recieved from R/C unit

  tone(2, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

}
void loop () {
  //string outString;
  valLB = digitalRead(pinLB);
  valLF = digitalRead(pinLF);
  valRB = digitalRead(pinRB);
  valRF = digitalRead(pinRF);


  // Serial << "LB, LF, RB, RF = " << valLB << ", " << valLF << endl;
  //Serial.print(outString );
  Serial.print("LB, LF, RB, RF = " );
  Serial.print(valLB);
  Serial.print(", ");
  Serial.print(valLF);
  Serial.print(", ");
  Serial.print(valRB);
  Serial.print(", ");
  Serial.println(valRF);

  if( (valLF == 0) && ( valLF  == 0 && valRF ) ) // forward button is pressed
  {
    servoLeft.writeMicroseconds(1700) ; // forward
    //   servoRight.writeMicroseconds(1300); // forward
  }
  if ( !valLF && (!valLF && valRB) )
  {  
    servoRight.writeMicroseconds(1300); // forward
    //   servoLeft.writeMicroseconds(1300); // back
    //    servoRight.writeMicroseconds(1700); // back
  }
  else
  {
    servoRight.writeMicroseconds(1500); // stop
    servoLeft.writeMicroseconds(1500); // stop
  } 

  //  if ( valRB == 0 ) 
  //  {
  //    servoRight.writeMicroseconds(1300); // back?
  //  }
  //  else if ( valRF == 0 )
  //  {  
  //    servoRight.writeMicroseconds(1700); // forward
  //  }
  //  else
  //  {
  //    servoRight.writeMicroseconds(1500); // stop
  //  } 
  delay(250);

  //  servoLeft.writeMicroseconds(1300); // clockwise
  //  servoRight.writeMicroseconds(1300); // clockwise
  //  delay(3000);
  //  servoLeft.writeMicroseconds(1700); // cntr-clockwise
  //  servoRight.writeMicroseconds(1700); // cntr-clockwise
  //  delay(3000);
  //  servoLeft.writeMicroseconds(1500); // stop
  //  servoRight.writeMicroseconds(1500); // stop

}









