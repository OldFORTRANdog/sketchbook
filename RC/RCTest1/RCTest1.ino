/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
 
int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

void setup() {

  pinMode(13, INPUT); // Set our input pins as such
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT); 
  pinMode(9, INPUT);
  pinMode(8, INPUT);

  Serial.begin(57600); // Pour a bowl of Serial

}

void loop() {

  ch1 = pulseIn(13, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(12, HIGH, 25000); // each channel
  ch3 = pulseIn(11, HIGH, 25000);
  ch4 = pulseIn(10, HIGH, 25000);
  ch5 = pulseIn(9, HIGH, 25000);
  ch6 = pulseIn(8, HIGH, 25000);

  Serial.print("Channel 1: ");
  Serial.print(ch1);        // each channel
  Serial.print(", Right X = ");
  Serial.println(map(ch1,1142,1862,-127,127));        // each channel

  Serial.print("Channel 2: ");
  Serial.print(ch2);        // each channel
  Serial.print(", Right Y = ");
  Serial.println(map(ch2,1146,1791,-127,127));        // each channel

  Serial.print("Channel 3:");
  Serial.println(ch3);

  Serial.print("Channel 4:");
  Serial.println(ch4);

  Serial.print("Channel 5:");
  Serial.println(ch5);

  Serial.print("Channel 6:");
  Serial.println(ch6);
  Serial.println("");

  delay(1000); // I put this here just to make the terminal 
              // window happier
}
