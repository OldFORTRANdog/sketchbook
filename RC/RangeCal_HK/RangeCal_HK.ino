// Test of Calibration & range of HobbyKing RC unit.
// Even averaging 20 readings with pulseIn gives pretty noisy data.


// declare R/C pins and variables
#define RC1 4 // Use precompiler statements to define pins; they are constants
#define RC2 8

int ch1; // Right Joysteck, Left - Right reading
int ch2; // Right Joysteck, Front - Back reading
//int ch3; // Left Joysteck, Front - Back reading
//int ch4; // Left Joystick, Left - Right reading
//int ch5; // VR(A)
//int ch6; // VR(B)

float aveCh1=0;
float aveCh2=0;
byte nread = 1;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("X-Holonomic R/C drive Test");

 }

void loop() {
    // Read values
  ch1 = pulseIn(RC1, HIGH, 25000)-1450; // Gives X range to 0 - 1014
  ch2 = pulseIn(RC2, HIGH, 25000)-1510; // Gives Y range to 0 - 875
  // Make sure they are not negative and scale -500 to 500.
  ch1 = map(ch1,0,1014,-500, 500);
  ch2 = map(ch2,0,875,-500, 500);
  /* Serial.print("Ch1 = "); */
  /* Serial.print(ch1); */
  /* Serial.print(", Ch2 = "); */
  /* Serial.println(ch2); */
  // Check for the 0 point here by Uncommenting the above section
 
  aveCh1 +=ch1;
  aveCh2 +=ch2;
  nread ++;
  if( nread == 20 ) {

    Serial.print("aveCh1 = ");
    Serial.print(aveCh1/nread);
    Serial.print(", aveCh2 = ");
    Serial.println(aveCh2/nread);
    aveCh1 = 0;
    aveCh2 = 0;
    nread = 1;
  }
}
