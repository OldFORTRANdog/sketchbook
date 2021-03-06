/*
  touch2sonic2:
  Uses PING(( and HCSR04 Sonar sensor and has 2 buttons for 
  touch sensors that turn on an LED when button is pushed
 */
#include <NewPing.h> 

const byte led1Pin = 12;
const byte led2Pin = 13;
const byte touch1Pin = 11;
const byte touch2Pin = 10;
const int pingPin = 7;
const int sonicTriggerPin = 8;
const int sonicEchoPin = 9;
//Define new sonar sensor
NewPing pPing(pingPin, pingPin, 500);
NewPing sonar(sonicTriggerPin, sonicEchoPin, 500);


// the setup routine runs once when you press reset:
void setup() {   
  Serial.begin(9600);
             
  // initialize the digital pin as an output.
  pinMode(led1Pin, OUTPUT);   
  pinMode(touch1Pin, INPUT);
  pinMode(touch2Pin, INPUT);
  pinMode(pingPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if(digitalRead(touch1Pin) == HIGH ) {
    digitalWrite(led1Pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(led1Pin, LOW);
  }
  if(digitalRead(touch2Pin) == HIGH ) {
    digitalWrite(led2Pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(led2Pin, LOW);
  }
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  /* pinMode(pingPin, OUTPUT); */
  /* digitalWrite(pingPin, LOW); */
  /* delayMicroseconds(2); */
  /* digitalWrite(pingPin, HIGH); */
  /* delayMicroseconds(5); */
  /* digitalWrite(pingPin, LOW); */

  

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  //pinMode(pingPin, INPUT);
  //duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  //cm = microsecondsToCentimeters(duration);
  
  //  Serial.print(inches);
    int sonicInches = sonar.ping_in();
    int pingInches = pPing.ping_in();
    Serial.print("Ping inches = ");
    Serial.print(pingInches);
    //Serial.print("XXXX");
  Serial.print("; Sonic sensor inches = ");
  Serial.print(sonicInches);
  Serial.println();
  
  delay(100);

}
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
