// RCHolo1: Reads Intereupts for X and Y coords
//
//
// include the pinchangeint library - see the links in the related topics section above for details
#include <PinChangeInt.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);
int ch1; // Right Joysteck, Left - Right reading
int ch2; // Right Joysteck, Front - Back reading
//int ch3; // Left Joysteck, Front - Back reading
//int ch4; // Left Joystick, Left - Right reading
//int ch5; // VR(A)
//int ch6; // VR(B)

float theta;
float magnitude;
float vx, vy;
float w1, w2, w3, w4;
byte w1_speed, w2_speed, w3_speed, w4_speed;
byte w1_Dir, w2_Dir, w3_Dir, w4_Dir;
const float sinCos45 = cos(45.0);


// Assign your channel in pins
#define THROTTLE_IN_PIN 2
#define STEERING_IN_PIN 3
//#define AUX_IN_PIN 4


// These bit flags are set in bUpdateFlagsShared to indicate which
// channels have new signals
#define THROTTLE_FLAG 1
#define STEERING_FLAG 2
//#define AUX_FLAG 4

// holds the update flags defined above
volatile uint8_t bUpdateFlagsShared;

// shared variables are updated by the ISR and read by loop.
// In loop we immediatley take local copies so that the ISR can keep ownership of the 
// shared ones. To access these in loop
// we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals
volatile uint16_t unThrottleInShared;
volatile uint16_t unSteeringInShared;
//volatile uint16_t unAuxInShared;

// These are used to record the rising edge of a pulse in the calcInput functions
// They do not need to be volatile as they are only used in the ISR. If we wanted
// to refer to these in loop and the ISR then they would need to be declared volatile
uint32_t ulThrottleStart;
uint32_t ulSteeringStart;
uint32_t ulAuxStart;

void setup()
{
  Serial.begin(9600);
  Serial.println("RCHolo1");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Turn off all motors
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);

  // using the PinChangeInt library, attach the interrupts
  // used to read the channels
  PCintPort::attachInterrupt(THROTTLE_IN_PIN, calcThrottle,CHANGE); 
  PCintPort::attachInterrupt(STEERING_IN_PIN, calcSteering,CHANGE); 
  //  PCintPort::attachInterrupt(AUX_IN_PIN, calcAux,CHANGE); 
}

void loop()
{
  // create local variables to hold a local copies of the channel inputs
  // these are declared static so that thier values will be retained 
  // between calls to loop.
  static uint16_t unThrottleIn;
  static uint16_t unSteeringIn;
  //  static uint16_t unAuxIn;
  // local copy of update flags
  static uint8_t bUpdateFlags;

  // check shared update flags to see if any channels have a new signal
  if(bUpdateFlagsShared)  {
    noInterrupts(); // turn interrupts off quickly while we take local copies of the shared variables

    // take a local copy of which channels were updated in case we need to use this in the rest of loop
    bUpdateFlags = bUpdateFlagsShared;
    
    // in the current code, the shared values are always populated
    // so we could copy them without testing the flags
    // however in the future this could change, so lets
    // only copy when the flags tell us we can.
    
    if(bUpdateFlags & THROTTLE_FLAG)    {
      unThrottleIn = unThrottleInShared;
    }
    
    if(bUpdateFlags & STEERING_FLAG)    {
      unSteeringIn = unSteeringInShared;
    }
    
    /* if(bUpdateFlags & AUX_FLAG)   {*/
    /*   unAuxIn = unAuxInShared; */
    /* } */
     
    // clear shared copy of updated flags as we have already taken the updates
    // we still have a local copy if we need to use it in bUpdateFlags
    bUpdateFlagsShared = 0;
    
    interrupts(); // we have local copies of the inputs, so now we can turn interrupts back on
    // as soon as interrupts are back on, we can no longer use the shared copies, the interrupt
    // service routines own these and could update them at any time. During the update, the 
    // shared copies may contain junk. Luckily we have our local copies to work with :-)
  }
  
  // do any processing from here onwards
  // only use the local values unAuxIn, unThrottleIn and unSteeringIn, the shared
  // variables unAuxInShared, unThrottleInShared, unSteeringInShared are always owned by 
  // the interrupt routines and should not be used in loop
  
  // the following code provides simple pass through 
  // this is a good initial test, the Arduino will pass through
  // receiver input as if the Arduino is not there.
  // This should be used to confirm the circuit and power
  // before attempting any custom processing in a project.
  
  // we are checking to see if the channel value has changed, this is indicated  
  // by the flags. For the simple pass through we don't really need this check,
  // but for a more complex project where a new signal requires significant processing
  // this allows us to only calculate new values when we have new inputs, rather than
  // on every cycle.
  if(bUpdateFlags & THROTTLE_FLAG)   {
    unThrottleIn = unThrottleInShared;
    Serial.print("X is ");
    Serial.println(unThrottleIn);
  } else {
    Serial.print("unThrottleInShared is ");
    Serial.println(unThrottleInShared);
  }  
  if(bUpdateFlags & STEERING_FLAG)   {
    unSteeringIn = unSteeringInShared;
    Serial.print("Y is ");
    Serial.println(unSteeringIn);
  }
  
  //  if(bUpdateFlags & AUX_FLAG)   {
  //    if(servoAux.readMicroseconds() != unAuxIn)   {
  //      servoAux.writeMicroseconds(unAuxIn);
  //    }
  //  }
  //STEP 1: Convert the RC values
  //  ch1 = X;
  //  ch2 = Y;

  ch1 = map(unThrottleIn,1120,1892,-100,100); // X value, mapped -100 to 100
  ch2 = map(unSteeringIn,1175,1832,-100,100); // Y value, mapped -100 to 100
  //ch1 = int(unThrottleIn);
  //  ch2 = int(unSteeringIn);

  //STEP 2. Convert them to a direction vector centered at 0 straight ahead
  // i.e., not like a unit circle!
  float theta = atan2(ch1, ch2);
  float magnitude = sqrt((ch1*ch1) + (ch2*ch2) );

  Serial.print("Here ch1: ");
  Serial.print(ch1);
  Serial.print(" Here ch2: ");
  Serial.print(ch2);

  Serial.print(" Ang: ");
  Serial.print(degrees(theta));

  Serial.print(" Mag: ");
  Serial.println(magnitude);

  // magnitudes less than about 8 are neutral stick positions
  // and should probably just be ignored
  if(magnitude > 8.0f) {  

    float vx = magnitude * sin(theta);
    float vy = magnitude * cos(theta);

    float w1 = vx*sin(-45) + vy*cos(-45); // vx*cos(-45) + vy*sin(45) 
    float w3 = vx*sin(-45) + vy*cos(-45); // vx*cos(-45) + vy*sin(45) 
    float w4 = vx*sin( 45) + vy*cos( 45); // vx*cos( 45) + vy*sin(45) 
    float w2 = vx*sin( 45) + vy*cos( 45); // vx*cos( 45) + vy*sin(45) 

    byte w1_Dir, w2_Dir, w3_Dir, w4_Dir;
    if ( w1 < 0 ) {
      w1_Dir = BACKWARD;
    }
  else {
    w1_Dir = FORWARD;
  }

  if ( w2 < 0 ) {
    w2_Dir = BACKWARD;
  }
  else {
    w2_Dir = FORWARD;
  }
  
  if ( w3 < 0 ) {
    w3_Dir = BACKWARD;
  }
  else {
    w3_Dir = FORWARD;
  }
 
  if ( w4 < 0 ) {
    w4_Dir = BACKWARD;
  }
  else {
    w4_Dir = FORWARD;
  }
 
    byte w1_speed = (byte) map(abs(w1), 0, 100, 0, 254);
    byte w2_speed = (byte) map(abs(w2), 0, 100, 0, 255);
    byte w3_speed = (byte) map(abs(w1), 0, 100, 0, 255);
    byte w4_speed = (byte) map(abs(w2), 0, 100, 0, 255);
    Serial.print("This ch1: ");
    Serial.print(ch1);
    Serial.print(" That ch2: ");
    Serial.print(ch2);

    Serial.print(" Ang: ");
    Serial.print(degrees(theta));

    Serial.print(" Mag: ");
    Serial.print(magnitude);


    Serial.print(" vx: ");
    Serial.print(vx);
    Serial.print(" vy: ");
    Serial.print(vy);

    Serial.print(" w1 & w3 speed & uncal.: ");
    Serial.print(w1_speed);
    Serial.print(", ");
    Serial.print(w1);
    Serial.print(" w2 & w4 speed & uncal.: ");
    Serial.print(w2_speed);
    Serial.print(", ");
    Serial.print(w2);
    //    Serial.print(" w3: ");
    //    Serial.print(w3_speed);
    //    Serial.print(", ");
    //Serial.print(w3);
//    Serial.print(" w4: ");
//    Serial.print(w4_speed);
//    Serial.print(", ");
//    Serial.print(w4);
    Serial.println();
    //    delay(10);

    motor1->run(w1_Dir);
    motor2->run(w2_Dir);
    motor3->run(w3_Dir);
    motor4->run(w4_Dir);

    motor1->setSpeed(w1_speed);  
    motor2->setSpeed(w2_speed);  
    motor3->setSpeed(w3_speed);  
    motor4->setSpeed(w4_speed);  
    //   delay(1000);
  
  bUpdateFlags = 0;
}
}
// simple interrupt service routine
void calcThrottle()
{
  // if the pin is high, its a rising edge of the signal pulse, so lets record its value
  if(digitalRead(THROTTLE_IN_PIN) == HIGH)
  { 
    ulThrottleStart = micros();
  }
  else
  {
    // else it must be a falling edge, so lets get the time and subtract the time of the rising edge
    // this gives use the time between the rising and falling edges i.e. the pulse duration.
    unThrottleInShared = (uint16_t)(micros() - ulThrottleStart);
    // use set the throttle flag to indicate that a new throttle signal has been received
    bUpdateFlagsShared |= THROTTLE_FLAG;
  }
}

void calcSteering()
{
  if(digitalRead(STEERING_IN_PIN) == HIGH)
  { 
    ulSteeringStart = micros();
  }
  else
  {
    unSteeringInShared = (uint16_t)(micros() - ulSteeringStart);
    bUpdateFlagsShared |= STEERING_FLAG;
  }
}

/* void calcAux() */
/* { */
/*   if(digitalRead(AUX_IN_PIN) == HIGH) */
/*   {  */
/*     ulAuxStart = micros(); */
/*   } */
/*   else */
/*   { */
/*     unAuxInShared = (uint16_t)(micros() - ulAuxStart); */
/*     bUpdateFlagsShared |= AUX_FLAG; */
/*   } */
/* } */