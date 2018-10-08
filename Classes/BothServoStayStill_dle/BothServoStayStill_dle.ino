/* Servo testing */
#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop() {
  servoLeft.writeMicroseconds(1500);  // 1.5 ms = stay still signal
  servoRight.writeMicroseconds(1500);  // 1.5 ms = stay still signal
}

