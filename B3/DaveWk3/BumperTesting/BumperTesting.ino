#define LEFT_BUMP_PIN 47
#define RIGHT_BUMP_PIN 46

void setup() {
  pinMode(LEFT_BUMP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN, INPUT_PULLUP);
  Serial.begin(9600);  //Begin serial communcation
}

void loop(void) {
  if (!digitalRead(LEFT_BUMP_PIN)) {
    Serial.println ("Left bumper");
  }
  if (!digitalRead(RIGHT_BUMP_PIN)) {
    Serial.println ("Right bumper");
  }
  delay(500);
}

