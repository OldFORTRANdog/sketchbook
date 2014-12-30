// Interrupt Service Routine (ISR)
const byte LED = 13;
const byte XINT = 2;
const byte YINT = 3;
bool ledState = false;

// Interrupt Service Routine (ISR)
void pinChange ()
{
  ledState = !ledState;
}  // end of pinChange

void setup ()
{
  pinMode (LED, OUTPUT);  // so we can update the LED
  //  digitalWrite (, HIGH);  // internal pull-up resistor
  attachInterrupt (XINT, pinChange, CHANGE);  // attach interrupt handler
}  // end of setup

void loop ()
{
  // loop doing nothing 
} 