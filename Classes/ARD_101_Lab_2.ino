/*
  Alterations to Blink for:
  Makelab Charleston
  Class: ARD-101
  
  Lab 2

 */
 
// Pin 5 and 6 are PWM pins has an LED connected on most Arduino boards.
// give them a name:
int led_1 = 5;
int led_2 = 6;

//Fading Stuff
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
  analogWrite(led_1, brightness);           //LED 1 Fades Up
  analogWrite(led_2, 255-brightness);       //LED 2 Fades the opposite Way
  
  //Update brightness or nothing will happen
  brightness += fadeAmount;  //another way of saying brightness = brightness + fadeAmount;
  
  //invert so we fade in and out...
  if((brightness <= 0) || (brightness >= 255)) {
    fadeAmount = -fadeAmount;
  }
   
  //wait some time for next change
  delay(30);         
}
