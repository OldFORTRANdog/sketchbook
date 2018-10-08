/*
  Alterations to Blink for:
  Makelab Charleston
  Class: ARD-101
  
  Lab 3: Serial Controlled LEDs
*/
 
// Pin 5 and 6 are PWM pins has an LED connected on most Arduino boards.
// give them a name:
int led_1_pin = 5;
int led_2_pin = 6;

//Fading Stuff
int led_1_val = 0;
int led_2_val = 0;

//string stuff
char strValue[6]; //a character array... or a string
int index = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_1_pin, OUTPUT);   
  pinMode(led_2_pin, OUTPUT);    
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(led_1_pin, led_1_val);           //LED 1 Fades Up
  analogWrite(led_2_pin, led_2_val);       //LED 2 Fades the opposite Way
  
  if( Serial.available())
  {
    char ch = Serial.read(); // 
    if(index < 5 && isDigit(ch) ){
      strValue[index++] = ch; // add the ASCII character to the string;
    }
    else
    {
      // here when buffer full or on the first non digit
      strValue[index] = 0;        // terminate the string with a 0
      if((ch == 'A') || (ch == 'a')) {
        led_1_val = atoi(strValue);  // use atoi to convert the string to an int
      }
      else if((ch == 'B') || (ch == 'b')) {
        led_2_val = atoi(strValue);  // use atoi to convert the string to an int
      }
      index = 0;
    }
  }
}
