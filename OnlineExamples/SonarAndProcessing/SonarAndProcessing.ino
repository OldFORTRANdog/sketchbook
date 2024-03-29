/* This project uses the Adafruit Motor shield library (copyright Adafruit Industries LLC, 2009
 this code is public domain, enjoy!)
 
 The HC-SR04 sensor uses some code from the following sources:
 From Virtualmix: http://goo.gl/kJ8Gl
 Modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com/
 on 10 Nov 2012.
*/

#include <AFMotor.h>
#include <Servo.h> 

// DC hobby servo
Servo servo1;

/* The servo minimum and maximum angle rotation */
static const int minAngle = 0;
static const int maxAngle = 176;
int servoAngle;
int servoPos;
int servoPin = 10;


/* Define pins for HC-SR04 ultrasonic sensor */
#define echoPin A0 // Echo Pin = Analog Pin 0
#define trigPin A1 // Trigger Pin = Analog Pin 1
#define LEDPin 13 // Onboard LED
long duration; // Duration used to calculate distance
long HR_dist=0; // Calculated Distance
int HR_angle=0; // The angle in which the servo/sensor is pointing
int HR_dir=1; // Used to change the direction of the servo/sensor
int minimumRange=5; //Minimum Sonar range
int maximumRange=200; //Maximum Sonar Range

/*--------------------SETUP()------------------------*/
void setup() {
 //Begin Serial communication using a 9600 baud rate
 Serial.begin (9600);
 
 // Tell the arduino that the servo is attached to Digital pin 10.
 servo1.attach(servoPin);
 
 //Setup the trigger and Echo pins of the HC-SR04 sensor
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

/*----------------------LOOP()--------------------------*/
void loop() {
 
 /* check if data has been sent from the computer: */
 if (Serial.available()) {
 
 /* This expects an integer from the Serial buffer */
 HR_angle = Serial.parseInt();
 
 /* If the angle provided is 0 or greater, then move servo to that 
 position/angle and then get a reading from the ultrasonic sensor */
 if(HR_angle>-1){
 /*Make sure that the angle provided does not go beyond the capabilities
 of the Servo. This can also be used to calibrate the servo angle */
 servoPos = constrain(map(HR_angle, 0,180,minAngle,maxAngle),minAngle,maxAngle);
 servo1.write(servoPos);
 
 /* Call the getDistance function to take a reading from the Ultrasonic sensor */
 getDistance();
 }
 }
}

/*--------------------getDistance() FUNCTION ---------------*/
void getDistance(){ 
 
 /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 HR_dist = duration/58.2;
 
 /*Send the reading from the ultrasonic sensor to the computer */
 if (HR_dist >= maximumRange || HR_dist <= minimumRange){
 /* Send a 0 to computer and Turn LED ON to indicate "out of range" */
 Serial.println("0");
 digitalWrite(LEDPin, HIGH); 
 } else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(HR_dist);
 digitalWrite(LEDPin, LOW);
 }
}
