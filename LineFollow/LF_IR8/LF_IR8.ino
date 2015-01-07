// Test code for Parallax 8 IR-sensor line follower: -- IR8test
#include <Servo.h>

Servo servoLeft; 
Servo servoRight;

/* Logic: Assume straight is 
 servoLeft.writeMicroseconds(1645);   //Left goes counter clockwise
 servoRight.writeMicroseconds(1300);   //Right goes clockwise
 leftRange = 145 // from 1500 = stop
 rightRange = -200  // from 1500 = stop
 Then IR sensors 0, 1, and 2, will reduce speed of LEFT wheel by 100, 50, and 10% respectively 
 and IR 5, 6, and 7 will reduce speed of RIGHT wheel by 10, 50 , and 100, resp.
 Then??/
 */
int leftRange = 145; // from 1500 = stop
int rightRange = -200;  // from 1500 = stop
int leftNum, rightNum;
int leftFact, rightFact;
int lSpeed, rSpeed;

int enablePin = 10; 
int IRsens[] = {
  3, 4, 5, 6, A0, A1, A2, A3};
int seesDark[7];

//int EnablePin = 10;

void setup() {
  servoLeft.attach(12);      // Left on pin 12
  servoRight.attach(11);     // Right on pin 11
  servoLeft.writeMicroseconds(1645);   //Left goes counter clockwise
  servoRight.writeMicroseconds(1300);   //Right goes clockwise
  delay(100);

  // Define the input pins for the 8 IR sensors)
  for (int i = 0; i <= 7; i++) {
    pinMode(IRsens[i], INPUT);     // IR sensor Pin i
  }

  // Define INPUT pin  
  //pinMode(enablePin, OUTPUT);   // IR sensor Pin EN, Enable, pull low for low-power mode
  //digitalWrite(enablePin, LOW); // Set to low power mode

  Serial.begin(9600);

  tone(2, 3300, 500); // Play start tone for 1 second
  delay(1000);    // Wait for tone to end
  //  tone(2, 1300, 500); // Play start tone for 1 second
  //delay(1000);    // Wait for tone to end
}

void loop() {
  servoLeft.attach(12);      // Left on pin 12
  servoRight.attach(11);     // Right on pin 11
  Serial.println();
  Serial.print("seesDark = [ ");
  for (int i = 0; i < 8; i++) {
    seesDark[i] = digitalRead(IRsens[i]);
    Serial.print(seesDark[i]);
    if (i < 7) Serial.print(", ");
  }
  Serial.print(" ]"); 
  leftNum = (seesDark[0] + seesDark[1] + seesDark[2] );
  if( leftNum > 0 ) {
    leftFact = leftRange * (1 - ((( seesDark[0]*100 + seesDark[1]*50 + seesDark[2]*10 )/ leftNum )/100));
  }
  else {
    leftFact = leftRange;
  }
  Serial.print(", leftFact = ");
  Serial.print(1500 + leftFact); 

  rightNum = (seesDark[7] + seesDark[6] + seesDark[5] );
  if( rightNum > 0 ) {
    rightFact = rightRange * (1 - ((( seesDark[7]*100 + seesDark[6]*50 + seesDark[5]*10 )/ rightNum )/100.));
  }
  else {
    rightFact = rightRange;
  }
  Serial.print(", rightFact = ");
  Serial.print(1500 + rightFact);
  Serial.println();
  lSpeed = 1500 + leftFact;
  rSpeed = 1500 + rightFact;
  servoLeft.writeMicroseconds(lSpeed);   //Left goes counter clockwise
  servoRight.writeMicroseconds(rSpeed);   //Right goes clockwise

  delay(200);
}













