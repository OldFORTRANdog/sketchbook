/*
  Alterations to Blink for:
  Makelab Charleston
  Class: ARD-101
  
  Lab 4: Joystick Controlled LEDs
*/
 
// Define the Pins we are using as constants
#define PIN_X_AXIS       A1
#define PIN_Y_AXIS       A0
#define PIN_PUSHBUTTON   A5

#define RANGE                3     // output range of X or Y movement
#define RESPONSE_DELAY       2      // response delay of the mouse, in ms
#define THRESHOLD            2      // resting threshold
#define MIN_READING          0      // actual analogRead minima for {x, y}
#define MAX_READING          1023   // actual analogRead maxima for {x, y}

//values
int xAxisVal = 0;
int yAxisVal = 0;
int pbVal = 0;

int  buttonState = 1;
int  lastButtonState = 1;
long lastDebounceTime = 0;
long debounceDelay = 50;

// the setup routine runs once when you press reset:
void setup() {                 
  pinMode(PIN_X_AXIS, INPUT);   
  pinMode(PIN_Y_AXIS, INPUT);   
  pinMode(PIN_PUSHBUTTON, INPUT_PULLUP);   
  Serial.begin(9600);
  Mouse.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  xAxisVal  = readAxis(PIN_X_AXIS);
  yAxisVal  = readAxis(PIN_Y_AXIS);
  pbVal     = checkButton();
  
  Serial.print(xAxisVal);
  Serial.print('\t');
  Serial.print(yAxisVal);  
  Serial.print('\t');
  Serial.println(pbVal);
    
  if(xAxisVal || yAxisVal) {
    Mouse.move(xAxisVal, yAxisVal, 0);
  }
  
  if(pbVal == 0) {
    Mouse.press();
  }
  else if(pbVal == 1) {
    Mouse.release();
  }
  
  delay(RESPONSE_DELAY);  
  
}

int readAxis(int axisPin) {
  int distance = 0;    // distance from center of the output range

  // read the analog input:
  int reading = analogRead(axisPin);

  // map the reading from the analog input range to the output range:
  reading = map(reading, MIN_READING, MAX_READING, -RANGE, RANGE);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  if (abs(reading) >= THRESHOLD) {
    distance = reading;
  } 

  // return the distance for this axis:
  return distance;
}

int checkButton(void) {
  // read the state of the switch into a local variable:
  int output = -1;
  int reading =  digitalRead(PIN_PUSHBUTTON);
  
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
   if ((millis() - lastDebounceTime) > debounceDelay) {
     if (reading != buttonState) {
       buttonState = reading;
       output = reading;
     }
   }
   
   lastButtonState = reading;
   
   return output; 
   // will return:
  // -1 = no change 
  //  0 = button just changed to pressed
  //  1 = button just changed to not pressed
}
