// BOE shield - Hooking to HobbyKing RC unit
//
//#use Serial
#include <Servo.h>
//Servo servoLeft;
//Servo servoRight;


// declare R/C pins and variables
int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

int pinch1 = 10;
int pinch2 = 9;
int pinch3 = 8;
int pinch4 = 7;
int pinch5 = 6;
int pinch6 = 5;

void setup() {

  tone(2, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(pinch1, INPUT); // Set our input pins as such
  pinMode(pinch2, INPUT);
  pinMode(pinch3, INPUT);
  pinMode(pinch4, INPUT); 
  pinMode(pinch5, INPUT);
  pinMode(pinch6, INPUT);

  Serial.begin(57600); 
}

void loop() {

  ch1 = pulseIn(pinch1, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(pinch2, HIGH, 25000); // each channel
  ch3 = pulseIn(pinch3, HIGH, 25000);
  ch4 = pulseIn(pinch4, HIGH, 25000);
  ch5 = pulseIn(pinch5, HIGH, 25000);
  ch6 = pulseIn(pinch6, HIGH, 25000);

  Serial.print("Channel 1: ");
  Serial.print(ch1);        // each channel
  Serial.print(", Right X = ");
  Serial.println(map(ch1,1142,1862,-127,127));        // each channel

  Serial.print("Channel 2: ");
  Serial.print(ch2);        // each channel
  Serial.print(", Right Y = ");
  Serial.println(map(ch2,1146,1791,-127,127));        // each channel

  Serial.print("Channel 3:");
  Serial.println(ch3);

  Serial.print("Channel 4:");
  Serial.println(ch4);

  Serial.print("Channel 5:");
  Serial.println(ch5);

  Serial.print("Channel 6:");
  Serial.println(ch6);
  Serial.println("");

  delay(1000); // delay for ease in reading
}
