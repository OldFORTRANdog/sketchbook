/* RGB Common Cathode Demo Program
	Dave Eslinger, 19 July, 2016
	GoSciTech Ardino RObotics Course */

#include <TimedAction.h>	

TimedAction timedAction1 = TimedAction(10000,rainbow);
	
const byte RED_PIN = 7;
const byte GREEN_PIN = 6;
const byte BLUE_PIN = 5;
const int SPEED = 1;
int r, g, b; // our color values, 0-255

void setup() {
  // put your setup code here, to run once:
pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);
r = 255;
b = 0;
}

void loop() {
	timedAction1.check();
/*   // Begin with full red only.
	for (int i = 0; i <= 255; i++) { // Ramp UP Green
		g = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Yellow
	for(int i = 255; i >= 0; i--) { // Ramp down Red
		r = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is pure Green
	for (int i = 0; i <=255; i++){ // Ramp up Blue
		b = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Cyan
	for(int i = 255; i >= 0; i--) { // Ramp down Green
		g = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is pure Blue
	for (int i = 0; i <=255; i++){ // Ramp up Red
		r = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Magenta
	for (int i = 255; i >= 0; i--) { // Ramp down Blue
		b = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now we are back to pure red, so repeat!	
 */}

void rainbow() {
  // Begin with full red only.
	for (int i = 0; i <= 255; i++) { // Ramp UP Green
		g = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Yellow
	for(int i = 255; i >= 0; i--) { // Ramp down Red
		r = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is pure Green
	for (int i = 0; i <=255; i++){ // Ramp up Blue
		b = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Cyan
	for(int i = 255; i >= 0; i--) { // Ramp down Green
		g = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is pure Blue
	for (int i = 0; i <=255; i++){ // Ramp up Red
		r = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now it is Magenta
	for (int i = 255; i >= 0; i--) { // Ramp down Blue
		b = i;
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
		analogWrite(BLUE_PIN, b);
		delay(SPEED);
	}
// Now we are back to pure red, so repeat!	
}
