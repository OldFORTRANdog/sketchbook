#define LED_PIN         13

uint8_t ledState = 0;

void setup() {                
  pinMode(LED_PIN, OUTPUT);
  pinMode(7, INPUT_PULLUP); 
  attachInterrupt(4,blinkLED,FALLING);
 
}

void loop() {
}

void blinkLED() {
  digitalWrite(LED_PIN, ledState);
  ledState = !ledState;
}
