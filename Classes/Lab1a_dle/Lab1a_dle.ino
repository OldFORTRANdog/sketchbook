/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led_1 = 5;
int led_2 = 6;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_1, OUTPUT);     
  pinMode(led_2, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  for ( int i = 0; i < 5; i++ ) {
    digitalWrite(led_1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led_2, LOW);    // turn the LED off by making the voltage LOW
    delay(500);               // wait for a second
    digitalWrite(led_2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led_1, LOW);    // turn the LED off by making the voltage LOW
    delay(500);               // wait for a second
  }
}
