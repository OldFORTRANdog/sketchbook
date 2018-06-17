/*
  Morse Code program by Dave Eslinger, 

   Turns on and off the LED based on a set of dits, dahs, and spaces to 
  send a Morse coded message. 
  
  Based on the Blink program, with some simple modifications to
  show the Switch/Case statement.

  In Morse code, signal durations are arbitrary, but are set relative to 
  duration of a dot (also called a dit). This is one unit of time.
  Dashes (also know as dahs) are three units long.
  Components within a character are seperated by one unit of time. 
  Characters in a word are seprrated by three units of time.
  Words are seperated by seven units of time. 
  
  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  BLINK modified 8 May 2014 by Scott Fitzgerald
  Morse modified 2 July 2016 by Dave Eslinger
  
 */

 
// Define global variables to be used throughout the program

int baseTime = 100;  // The length in milliseconds of one dit
String phrase = "-.- ....- -.. .-.. . | "; // K4DLE, Dave's Ham call sign
int onMult; // varible for how long, relatively, to turn on LED
int offMult; // varible for how long, relatively to turn off LED

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  delay(2000);  // Wait 2 seconds to begin sending the message.  
}

// the loop function runs over and over again forever
void loop() {
	for (int i = 0; i <= phrase.length()-1; i++) {
		char signal = phrase[i];
		switch (signal) {
			case '.':
				onMult = 1;
				offMult = 1;
				break;
			case '-':
				onMult = 3;
				offMult = 1;
				break;
			case ' ':
				onMult = 0;
				offMult = 3;
				break;
			case '|':
				onMult = 0;
				offMult = 1;    // Only 1 because it is always surrounded
								// by spaces, so 3+1+3 gives the needed 7
				break;
			default:            // This is an error in our case so
				onMult = 10;    // send a long on then off signal
				offMult = 10;
		}
	  if (onMult > 0) {
		digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
		delay(baseTime*onMult);  // wait for the required time
	  }
	  digitalWrite(13, LOW);     // turn the LED off by making the voltage LOW
	  delay(baseTime*offMult);   // wait for the required time		
	}
	//delay(1000);
}
