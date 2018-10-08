#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


float pi = 3.1415926;

void setup() {                
  Serial.begin(9600);
  
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  
  Serial.println("Initialized");
  
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  delay(500);  
  Serial.println(time, DEC);


  // large block of text
  tft.setTextSize(2);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.print(pi, 3);
  tft.println(" Want pi?");
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setCursor(0, 20);
  tft.print(pi, 6);
  tft.println(" Want pi?");  
}

void loop() {

}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
