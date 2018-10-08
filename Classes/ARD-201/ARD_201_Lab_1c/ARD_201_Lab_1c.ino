#include <TimerOne.h>

#define LED_PIN         13
#define LED_BLINK_TIME  5000000

uint8_t ledState = 0;

void setup() {                
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600); 
  Timer1.initialize( LED_BLINK_TIME );
  Timer1.attachInterrupt(blinkLED);
}

void loop() {
  while(Serial.available() > 0) {
    Serial.write(Serial.read());
  }            
}

void blinkLED() {
  digitalWrite(LED_PIN, ledState);
  ledState = !ledState;
}
