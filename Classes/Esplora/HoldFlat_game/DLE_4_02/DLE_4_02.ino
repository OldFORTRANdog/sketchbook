// sketch 3-06
#define ledPin 13
int delayPeriod = 250;
int count =0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
    flash(20, delayPeriod);
  delay(3000);
}

void flash(int numFlashes, int d) {
  for (int i = 0; i < numFlashes; i++ ) {
  digitalWrite(ledPin, HIGH);
  delay(d);
  digitalWrite(ledPin, LOW);
  delay(d);
  }
} 


