/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led_1 = 5;
int led_2 = 6;

//Fading stuff
int brightness = 0;
int fadeAmount = 5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_1, OUTPUT);     
  pinMode(led_2, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  
  //Update brightness
  analogWrite(led_1, brightness);
  analogWrite(led_2,255-brightness);
  brightness += fadeAmount;
  
  if (( brightness <= 0 ) || (brightness >= 255) ) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
 
}
