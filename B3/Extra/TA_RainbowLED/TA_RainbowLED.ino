/* Timed Action RGB Common Cathode Demo Program
	Dave Eslinger, 10 September, 2016
*/

#include <TimedAction.h>
#include <Wire.h>
#include <NewPing.h>
#include <Servo.h>
#include <breadboardbot.h>


// Define Servos 
Servo panServo;
Servo tiltServo;


const byte LEFT_LED_PIN = 31;
const byte RIGHT_LED_PIN = 30;
const byte SONIC_TRIGGER_PIN = 51;
const byte SONIC_ECHO_PIN = 50;

const byte RED_PIN = 7;
const byte GREEN_PIN = 6;
const byte BLUE_PIN = 5;
const int RBSPEED = 2;  // Increment for rainbow 
int r, g, b; // our color values, 0-255
int rbTheta = 0;
boolean leftLED = 0;
boolean rightLED = 1;
// Sonic sensor
const float TARGET_DISTANCE_INCHES = 10; 
const int MAX_SONIC_DISTANCE = 500;      // cm, optional, 500 cm is default
/* Define new untrasonic sensor with trigger & echo pins and
   the maximum distance to be sensed. */
NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE);
int pingTime; // time in microseconds for a ping to return
float pingDist; // define variable to use for distance measurements

void Rainbow(int theta){
	r = constrain(map((1000)*(sin(2.*PI*theta/1023))/2.,-500,500,-85,341),0,255);
	g = constrain(map((1000)*(sin(2.*PI*(theta-341)/1023))/2.,-500,500,-85,341),0,255);
	b = constrain(map((1000)*(sin(2.*PI*(theta+341)/1023))/2.,-500,500,-85,341),0,255);

    analogWrite(RED_PIN, r);
    analogWrite(GREEN_PIN, g);
    analogWrite(BLUE_PIN, b);
//	String foo = "theta, r,g,b = " + String(theta) + ", " + String(r) + ", " + String(g) + ", " + String(b);
//	Serial.println(foo);
}

void SwapLED(void) {
//	String statusString = "Left is " + String(leftLED) + ", Right is " + String(rightLED);
//	Serial.println(statusString);
	digitalWrite(LEFT_LED_PIN,leftLED);
	digitalWrite(RIGHT_LED_PIN,rightLED);
	leftLED = !leftLED;
	rightLED = !rightLED;
}

void SonicRead(void){
 int i = 1;
}

//TimedAction timedAction1 = TimedAction(5000, Rainbow);
TimedAction timedAction2 = TimedAction(200, SwapLED);
//TimedAction timedAction3 = TimedAction(5000, SonicRead);

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(SONIC_TRIGGER_PIN,OUTPUT);
  pinMode(SONIC_ECHO_PIN,INPUT);

  Rainbow(rbTheta);

  digitalWrite(LEFT_LED_PIN,leftLED);
  digitalWrite(RIGHT_LED_PIN,rightLED);

  Serial.begin(9600);
}

void loop() {
	pingTime = sonic.ping();
/*	while (pingTime == 0) {
		pingTime = sonic.ping();
	}
    pingDist = Distance_inches(pingTime); */
	if(pingTime > 0) {
		timedAction2.setInterval(Distance_inches(pingTime)*50);
	}
//  timedAction1.check();
	rbTheta >= 1023-RBSPEED ?  rbTheta = 0 :  rbTheta += RBSPEED ;
	Rainbow(rbTheta);
	timedAction2.check();
}


