/* 
 Robotics with the BOE Shield - ServoSlowMoCcw
 Send 1/100th speed servo signals for viewing with an LED.
 */

void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(2);
  digitalWrite(13, LOW);
  delay(18);
}

