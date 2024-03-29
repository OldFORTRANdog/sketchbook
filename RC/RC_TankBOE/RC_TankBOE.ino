// BOE shield - Hooking to HobbyKing RC unit
// Tank Drive Test
//#use Serial
#include <Servo.h>
Servo servoLeft;
Servo servoRight;


// declare R/C pins and variables
int ch1; // Right Joysteck, Left - Right reading
int ch2; // Right Joysteck, Front - Back reading
int ch3; // Left Joysteck, Front - Back reading
int ch4; // Left Joystick, Left - Right reading
int ch5; // VR(A)
int ch6; // VR(B)

int pinch1 = 10;
int pinch2 = 9;
int pinch3 = 8;
int pinch4 = 7;
int pinch5 = 6;
int pinch6 = 5;
int leftMotor, rightMotor;

void setup() {
  servoLeft.attach(12);
  servoRight.attach(11);
  tone(2, 3400, 500);                       // Play tone for 1 second
  delay(500);                               // Delay to finish tone

  //  pinMode(pinch1, INPUT); // Set our input pins as such
  pinMode(pinch2, INPUT);
  pinMode(pinch3, INPUT);
  //pinMode(pinch4, INPUT); 
  //  pinMode(pinch5, INPUT);
  //  pinMode(pinch6, INPUT);

  Serial.begin(57600); 
}

void loop() {
 
  //  ch1 = pulseIn(pinch1, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(pinch2, HIGH, 25000); // each channel
  ch3 = pulseIn(pinch3, HIGH, 25000);
  //  ch4 = pulseIn(pinch4, HIGH, 25000);
  //  ch5 = pulseIn(pinch5, HIGH, 25000);
  //  ch6 = pulseIn(pinch6, HIGH, 25000);


  Serial.print("Channel 2: ");
  Serial.print(ch2);        // each channel
  Serial.print(", Right = ");
  Serial.print(map(ch2,1150,1800,-200,200));        // each channel

  Serial.print("    Channel 3:");
  Serial.print(ch3);
  Serial.print(", Left = ");
  Serial.print(map(ch3,1150,1800,-200,200));        // each channel
  rightMotor = 1500 - map(ch2,1150,1800,-200,200);
  leftMotor = 1500 + map(ch3,1150,1800,-200,200);
  servoLeft.writeMicroseconds(leftMotor);
  servoRight.writeMicroseconds(rightMotor);
  Serial.print(", servoLeft power = ");
  Serial.print(leftMotor);
  Serial.print(", servoRight power = ");
  Serial.println(rightMotor);

  delay(200); // delay for ease in reading
}
