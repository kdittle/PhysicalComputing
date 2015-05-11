#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_HX8357.h"
#include <stdint.h>
#include "TouchScreen.h"
#include <SPI.h>
#include <SD.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.

#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC);

#define SD_CS 4

#define YP A0  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

int fill = 298;
int incoming = 0;

int spaceBar = A2;
int spacePress = 45;
int spaceValue = 0;

int mouseButton = A3;
int mouse0Press = 45;
int mouseValue = 0;

void setup(void) 
{
//  pinMode(spaceBar, INPUT);
//  pinMode(mouseButton, INPUT);
//  Keyboard.begin();
//  Mouse.begin();
  
  Serial.begin(9600);
  tft.begin(HX8357D);
  tft.fillScreen(HX8357_WHITE);
  
  SD.begin(SD_CS);
  
  //Serial.print("Initializing SD card...");
  //if (!SD.begin(SD_CS)) 
  {
    //Serial.println("failed!");
  }
  //Serial.println("OK!");
  
  drawHealth(fill);
  drawMana();
}

void loop() 
{
  if(Serial.available() > 0)
 {
   incoming = Serial.read();
   if(incoming == 114)
   {
     fill = fill - 10;
     drawHealth(fill);
   }
 } 
 
 spaceValue = analogRead(spaceBar);
 //Serial.println(spaceValue);
 if(spaceValue > spacePress)
 {
   Keyboard.press('A');
 }
 else
 {
   Keyboard.release('A');
 }
 
 mouseValue = analogRead(mouseButton);
 //Serial.println(mouseValue);
 if(mouseValue > mouse0Press)
 {
   Mouse.click(MOUSE_LEFT);
 }
 else
 {
   Mouse.release(MOUSE_LEFT);
 }
}

void drawHealth(int x)
{
  tft.fillRect(11, 11, 300, 150, 0xFFFFFF);
  
  tft.drawRect(10, 10, 300, 150, 0xFFFFFF);
  tft.fillRect(11, 11, x, 148, 0xF800);
}

void drawMana()
{
  tft.drawRect(10, 160, 300, 150, 0x0000);
  tft.fillRect(11, 161, 298, 148, 0x001F);
}
