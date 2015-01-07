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
int pinBM = 5;
int pinFM = 4;
int pinRM = 6;
int pinLM = 7;
int valBM, valFM, valRM, valLM;

void setup() {
  Serial.begin(115200);
  servoLeft.attach(12);
  servoRight.attach(11);


  pinMode(pinBM, INPUT);
  digitalWrite(pinBM, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinFM, INPUT);
  digitalWrite(pinFM, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinRM, INPUT);
  digitalWrite(pinRM, HIGH); // pullup current unless signal recieved from R/C unit
  pinMode(pinLM, INPUT);
  digitalWrite(pinLM, HIGH); // pullup current unless signal recieved from R/C unit

  tone(2, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

}
void loop () {
  //string outString;
  valBM = !digitalRead(pinBM);		// Use ! on these since they are HIGH normally an dthe switches make them low
  valFM = !digitalRead(pinFM);
  valRM = !digitalRead(pinRM);
  valLM = !digitalRead(pinLM);


  // Serial << "BM, FM, RM, LM = " << valBM << ", " << valFM << endl;
  //Serial.print(outString );
  Serial.print("BM, FM, RM, LM = " );
  Serial.print(valBM);
  Serial.print(", ");
  Serial.print(valFM);
  Serial.print(", ");
  Serial.print(valRM);
  Serial.print(", ");
  Serial.print(valLM);

  int leftMotor, rightMotor;
	
	//leftMotor  = 1500 + 50 * ( valBM + valFM ) - 50 * valRM*vaBLM + 50 * valRM ;
	//rightMotor = 1500 - 50 * ( valBM + valFM ) - 50 * valFM*valLM - 50 * valRM ;
	//
	leftMotor  = 1500 + 200 * ( valFM - valBM - valLM + valRM );
	rightMotor = 1500 - 200 * ( valFM - valBM + valLM - valRM );
	
	servoLeft.writeMicroseconds(leftMotor);
	servoRight.writeMicroseconds(rightMotor);
  Serial.print(", servoLeft power = ");
  Serial.print(leftMotor);
  Serial.print(", servoRight power = ");
  Serial.println(rightMotor);

  //if( (valFM == 0) && ( valFM  == 0 && valLM ) ) // forward button is pressed
  //{
    //servoLeft.writeMicroseconds(1700) ; // forward
    ////   servoRight.writeMicroseconds(1300); // forward
  //}
  //if ( !valFM && (!valFM && valRM) )
  //{  
    //servoRight.writeMicroseconds(1300); // forward
    ////   servoLeft.writeMicroseconds(1300); // back
    ////    servoRight.writeMicroseconds(1700); // back
  //}
  //else
  //{
    //servoRight.writeMicroseconds(1500); // stop
    //servoLeft.writeMicroseconds(1500); // stop
  //} 

  //  if ( valRM == 0 ) 
  //  {
  //    servoRight.writeMicroseconds(1300); // back?
  //  }
  //  else if ( valLM == 0 )
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









