/* -----------------------------------------------------------
  Code for testing two TCRT5000 Optical Refelctance sensors.  Circuit and 
   basic code is from:
   http://www.foxytronics.com/learn/robots/kit-guides/line-follower-kit-guide/assembling-the-kit
  
   Initially Adapted by Dave Eslinger, 1/5/2015
   -----------------------------------------------------------*/


const int serialPeriod = 250;       // only print to the serial console every 1/4 second
unsigned long timeSerialDelay = 0;

// define variables to hold IR sensor readings
int irSensor0 = 0;
int irSensor1 = 0;
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}


// the loop routine runs over and over again forever
void loop() { 
    readIrSensors(); // read all of the IR sensors
    debugOutput();
}

// read all of the IR sensors
void readIrSensors() {
    irSensor0 = analogRead(A11);
    irSensor1 = analogRead(A12);
    delay(5); // delay 5ms
}

void debugOutput() {
    if((millis() - timeSerialDelay) > serialPeriod)
    {
        Serial.print("irSensor0: ");
        Serial.print(irSensor0);
        Serial.print(",  irSensor1: ");
        Serial.println(irSensor1);
        
        timeSerialDelay = millis();
    }
}