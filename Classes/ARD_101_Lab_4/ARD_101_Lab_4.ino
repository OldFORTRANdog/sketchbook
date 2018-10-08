/*
  Alterations to Blink for:
  Makelab Charleston
  Class: ARD-101
  
  Lab 4: Joystick Controlled LEDs
*/
 
// Define the Pins we are using as constants
#define PIN_LED_X        5
#define PIN_LED_Y        6
#define PIN_X_AXIS       A0
#define PIN_Y_AXIS       A1
#define PIN_PUSHBUTTON   A5

//Fading Stuff
int xAxisVal = 0;
int yAxisVal = 0;
int pbVal = 0;

//string stuff
char strValue[6]; //a character array... or a string
int index = 0;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(PIN_LED_X, OUTPUT);   
  pinMode(PIN_LED_Y, OUTPUT);    
  pinMode(PIN_X_AXIS, INPUT);   
  pinMode(PIN_Y_AXIS, INPUT);   
  pinMode(PIN_PUSHBUTTON, INPUT_PULLUP);   
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  xAxisVal  = analogRead(PIN_X_AXIS);
  yAxisVal  = analogRead(PIN_Y_AXIS);
  pbVal     = digitalRead(PIN_PUSHBUTTON);
  
  Serial.print(xAxisVal);
  Serial.print('\t');
  Serial.print(yAxisVal);  
  Serial.print('\t');
  Serial.println(pbVal);
    
  analogWrite(PIN_LED_X, xAxisVal/4);    
  analogWrite(PIN_LED_Y, yAxisVal/4);    
  
}
