/* 
   This is a test sketch for Holonomic-X drive BreadBoardBOt (BBbot, B^3) 
   Autonomous driving mode 
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; September, 2014
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h" // I don't think this is required


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define 'ports' M1, M2, M3 or M4 for motors.
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("X-Holonomic Autonomous drive Test");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Turn off all motors
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}
uint8_t i=0;
void loop() {
  i++;
  Serial.print("Loop count ");
  Serial.println(i);

  // Set speed (0-255) to be used for all manuevers
  motor1->setSpeed(200);  
  motor2->setSpeed(200);  
  motor3->setSpeed(200);  
  motor4->setSpeed(200);  

  motor1->run(FORWARD); // Drives forward
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  delay(500);

  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(500);

  motor1->run(BACKWARD); // strafes right
  motor2->run(FORWARD);
  motor3->run(BACKWARD);
  motor4->run(FORWARD);
  delay(500);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(500);

  motor1->run(BACKWARD); // Straight Backward
  motor2->run(BACKWARD);
  motor3->run(BACKWARD);
  motor4->run(BACKWARD);
  delay(500);

  motor1->run(RELEASE); //Pause
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(500);

  motor1->run(FORWARD); // Strafe left
  motor2->run(BACKWARD);
  motor3->run(FORWARD);
  motor4->run(BACKWARD);
  delay(500);

  motor1->run(RELEASE); // long pause
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(2000);

  motor1->run(FORWARD); // Spin clockwise
  motor2->run(BACKWARD);
  motor3->run(BACKWARD);
  motor4->run(FORWARD);
  delay(2000);

  motor1->run(RELEASE); // pause
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(2000);

  motor1->run(BACKWARD); // Spin Counterclockwise
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(BACKWARD);
  delay(2000);

  motor1->run(RELEASE); // Very long pause
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
  delay(5000);
}

