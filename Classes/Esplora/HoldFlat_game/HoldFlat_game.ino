// include the Esplora library
#include <Esplora.h>
int x_axis0 ;
int y_axis0 ;
int yError;
byte red = 0;
byte green = 0;
byte blue = 0;
boolean keepRunning;
boolean stopProgram;
int btnExit, btnNewGame;
int xZero = -15;
int yZero = -15;
const float xRange = 200;
const float yRange = 150;

void setup() {
  Serial.begin(9600);        // initialize serial communications 
  keepRunning = true;
}

void loop() 
{
  while (keepRunning) {

    btnExit = Esplora.readButton(SWITCH_DOWN); // Read and process exit button state
    if(btnExit == LOW) {
      keepRunning = false;
    }
    btnNewGame = Esplora.readButton(SWITCH_RIGHT);
    if ( btnNewGame == LOW ) {// reset the target x/y angle posotion
      xZero = -15. + xRange/2 - (xRange*rand())/RAND_MAX;
      yZero = -15. + yRange/2 - (yRange*rand())/RAND_MAX;
      Esplora.writeRed(125);
    }
    // read the x and y sensors into variables
    x_axis0 = Esplora.readAccelerometer(X_AXIS);
    y_axis0 = Esplora.readAccelerometer(Y_AXIS);
    red = 0;
    green = 0;
    blue = 0;
    int x_axis = x_axis0 - xZero;  // offest for non-zero center readout
    if (x_axis < -5 ) {
      // write the light levels to the Blue LED
      blue = abs(x_axis);
    }
    else if (x_axis > 5 ) {
      green = x_axis;
    }

    yError = y_axis0 - yZero;
    if( yError < -5 )   {
      Esplora.tone(200 + yError);
    }
    else if( yError > 5 ) {
      Esplora.tone(250 + yError);
    }
    else {
      Esplora.noTone();
    } 
    /*Serial.print("x_axis0=: ");      // print the label for X 
     Serial.print(x_axis0);      // print the value for the X axis
     Serial.print(", x_axis=");      // print the value for the X axis
     Serial.print(x_axis);      // print the value for the X axis
     Serial.print(",   y_axis0=: ");      // print the label for X 
     Serial.print(y_axis0);      // print the value for the X axis
     Serial.print(", xZero=");      // print the value for the X axis
     Serial.print(xZero);      // print the value for the X axis
     Serial.print(", yZero=");      // print the value for the X axis
     Serial.println(yZero);      // print the value for the X axis */
    // SHow color and add a small delay to keep the LED from flickering:
    Esplora.writeRGB(red, green, blue);
    delay(20);
  }
  Esplora.writeRGB(0,0,0);
  Esplora.noTone();
  while(1);

}


















