// Motor 1
byte forwardPin = 2;
byte backPin = 3;
byte speedPin = 9; // Needs to be a PWM pin to be able to control motor speed

byte parkPin = 6;
byte stopPin = 7;

unsigned long lastRunTime;
const unsigned long waitTime = 1000 * 10;

void setup() {  // Setup runs once per reset
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);

  //Define L298N Dual H-Bridge Motor Controller Pins

  pinMode(forwardPin, OUTPUT);
  pinMode(backPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(parkPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);

  lastRunTime = millis();
  Serial.println("Starting");
}

void loop() {

  // put your main code here, to run repeatedly:
  while (millis() - lastRunTime < waitTime) {
    Serial.println("Waiting");
  }
  Serial.println("Running");
  lastRunTime = millis();
  // Run motor out until we hit the stop switch
  while (digitalRead(stopPin) == HIGH) {
    Serial.println("Drive forward");
    analogWrite(speedPin, 255);//Sets speed variable via PWM
    digitalWrite(forwardPin, HIGH);
    digitalWrite(backPin, LOW);
  }
  Serial.println("Stop the motor");
  analogWrite(speedPin, 100);//Sets speed variable via PWM
  digitalWrite(forwardPin, HIGH);
  digitalWrite(backPin, HIGH);
  delay(1000);
  while (digitalRead(parkPin) == HIGH) {
    Serial.println("Drive backwards");
    analogWrite(speedPin, 255);//Sets speed variable via PWM
    digitalWrite(forwardPin, LOW);
    digitalWrite(backPin, HIGH);
  }
  Serial.println("Parked the motor");
  analogWrite(speedPin, 100);//Sets speed variable via PWM
  digitalWrite(forwardPin, HIGH);
  digitalWrite(backPin, HIGH);
  lastRunTime = millis();
  delay(5000);

}
