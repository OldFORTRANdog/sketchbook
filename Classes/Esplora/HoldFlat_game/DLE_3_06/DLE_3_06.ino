// sketch 3-06
int ledPin = 13;
int delayPeriod = 100;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(delayPeriod);
  digitalWrite(ledPin, LOW);
  delay(delayPeriod);
  delayPeriod += 200;
  if(delayPeriod > 1500)     delayPeriod = 100;
  
}


