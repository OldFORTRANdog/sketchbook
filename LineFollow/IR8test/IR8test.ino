// Test code for Parallax 8 IR-sensor line follower: -- IR8test
//int IRsensor0 = 2;
int IRsensor1 = 3;
int IRsensor2 = 4;
int IRsensor3 = 5;
int IRsensor4 = 6;
int IRsensor5 = 7;
int IRsensor6 = 8;
int IRsensor7 = 9;
int IRsensor8 = 10;
//int EnablePin = 10;

void setup() {
  // Define the input pins for the 8 IR sensors)
  // pinMode(IRsensor0, INPUT);     // IR sensor Pin 0
  pinMode(IRsensor1, INPUT);     // IR sensor Pin 1
  pinMode(IRsensor2, INPUT);     // IR sensor Pin 2
  pinMode(IRsensor3, INPUT);     // IR sensor Pin 3
  pinMode(IRsensor4, INPUT);     // IR sensor Pin 4
  pinMode(IRsensor5, INPUT);     // IR sensor Pin 5
  pinMode(IRsensor6, INPUT);     // IR sensor Pin 6
  pinMode(IRsensor7, INPUT);     // IR sensor Pin 7
  pinMode(IRsensor8, INPUT);     // IR sensor Pin 7
  // Define INPUT pin  
  //pinMode(EnablePin, OUTPUT);   // IR sensor Pin EN, Enable, pull low for low-power mode
  //digitalWrite(EnablePin, LOW); // Set to low power mode
  Serial.begin(9600);

  tone(2, 3300, 500); // Play start tone for 1 second
  delay(1000);    // Wait for tone to end
  tone(2, 1300, 500); // Play start tone for 1 second
  delay(1000);    // Wait for tone to end
}

void loop() {
  int IR0 = digitalRead(IRsensor1);
  Serial.println(IR0);
  delay(5000);
}





