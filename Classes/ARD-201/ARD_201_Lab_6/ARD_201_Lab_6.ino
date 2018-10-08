#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_MMA8451.h>
#include <DHT.h>

//Declare External Components
RTC_DS1307 rtc;
Adafruit_BMP085_Unified pressureSensor = Adafruit_BMP085_Unified(10085);
Adafruit_TSL2561_Unified lightSensor = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Adafruit_MMA8451 accelerometer = Adafruit_MMA8451();

#define DHTTYPE           DHT11     // DHT 11 
#define DHTPIN            3         // Pin which is connected to the DHT sensor.
DHT humiditySensor(DHTPIN, DHTTYPE);

#define LED_PIN 13

uint32_t delayMS;

void setup() {
  sensor_t sensor;
  
  //Initialize Busses
  Serial.begin(9600);
  Wire.begin();
  pinMode(LED_PIN, OUTPUT); 
  
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(5000); //give the user time to connect the serial monitor
  digitalWrite(LED_PIN, LOW);
  
  /*
  //Init Real Time Clock
  rtc.begin();
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }  
  */
  
  //initialize pressure sensor
  while(!pressureSensor.begin())
  {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    delay(100);
  }
  pressureSensor.getSensor(&sensor);
  displaySensorDetails(&sensor);
  
  //initialize Light sensor
  while(!lightSensor.begin())
  {

    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    delay(100);
  }
  lightSensor.getSensor(&sensor);
  displaySensorDetails(&sensor);
  configureLightSensor();
  
  //initialize Humidity Sensor
  humiditySensor.begin();
  
   while (! accelerometer.begin()) {
    Serial.println("Couldnt start Accelerometer");
  }
  accelerometer.setRange(MMA8451_RANGE_2_G);
  accelerometer.getSensor(&sensor);
  displaySensorDetails(&sensor);
  
  
  delay(2000);
  
}


void loop() {
  //Declare Event Variables
  sensors_event_t pressureEvent;
  sensors_event_t lightEvent;
  sensors_event_t accelerometerEvent;
  float humidity = humiditySensor.readHumidity();
  float humidityTemp = humiditySensor.readTemperature(); 
  float pressureTemperature = 0;
  
  pressureSensor.getEvent(&pressureEvent);
  lightSensor.getEvent(&lightEvent);
  accelerometer.getEvent(&accelerometerEvent);
  //Get events from sensors and print them
  
  if (pressureEvent.pressure)
  {
    Serial.print("Pressure:    ");
    Serial.print(pressureEvent.pressure);
    Serial.println(" hPa");

    pressureSensor.getTemperature(&pressureTemperature);
    Serial.print("Temperature: ");
    Serial.print(pressureTemperature);
    Serial.println(" C");    
  }
  else {
    Serial.println("Sensor error");
  }    
  
  //Light Sensor

  if (lightEvent.light)
  {
    Serial.print("Light:       ");
    Serial.print(lightEvent.light);
    Serial.println(" lux");
  }
  else
  {
    Serial.println("Sensor overload");
  }
  
  if (isnan(humidityTemp) || isnan(humidity)) {
    Serial.println("Error reading DHT11!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(humidityTemp);
    Serial.println(" *C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");    
  }
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: \t"); Serial.print(accelerometerEvent.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(accelerometerEvent.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(accelerometerEvent.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 ");  
  
  //Get Date and print it
/*  DateTime now = rtc.now();
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();*/


  Serial.println();
  Serial.println();  
  delay(2000);
}



/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(sensor_t *sensor) {
  
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor->name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor->version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor->sensor_id);
  Serial.print  ("Max Value:    "); Serial.println(sensor->max_value); 
  Serial.print  ("Min Value:    "); Serial.println(sensor->min_value); 
  Serial.print  ("Resolution:   "); Serial.println(sensor->resolution);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void configureLightSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // lightSensor.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // lightSensor.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  lightSensor.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  //lightSensor.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // lightSensor.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  lightSensor.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */  
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("402 ms");
  Serial.println("------------------------------------");
}
