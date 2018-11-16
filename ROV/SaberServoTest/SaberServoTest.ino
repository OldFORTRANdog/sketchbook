#include <Servo.h>
Servo myservo;

void setup () {
  myservo.attach(14); // Use PWM pin 14 to control Sabertooth.
}

void loop() {
  // 0 means full power in one direction.
  // Actually the minimum value for me is around 30.
  // A smaller value won't drive the motor.
  myservo.write(20);
  delay(5000);

  // 90 means stopping the motor.
  myservo.write(90);
  delay(2000);

  // 180 means full power in the other direction.
  // Actually the maximum value for me is around 160.
  // A larger value won't drive the motor either.
  myservo.write(160);
  delay(1000);
}
