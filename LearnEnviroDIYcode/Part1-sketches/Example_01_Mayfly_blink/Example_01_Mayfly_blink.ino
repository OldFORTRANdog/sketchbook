/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. On the Mayfly there are LEDs
  at pins 8 and 9. If you're unsure what pin the on-board LED is connected
  to on your Arduino model, check the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  modified 9 February 2018 for Mayfly
  by Beth Fisher
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 8 as an output.
  // green LED on Mayfly logger
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second
}
