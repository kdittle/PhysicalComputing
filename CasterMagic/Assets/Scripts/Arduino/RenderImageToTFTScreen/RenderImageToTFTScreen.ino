#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_HX8357.h"
#include <SPI.h>
#include <SD.h>
#include <stdint.h>
#include "TouchScreen.h"


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

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define ARRAYSIZE 2
char *images[ARRAYSIZE] = {"ASI.bmp", "ASI2.bmp"};

int lastX = 0;
int curX = 0;
int distX = 100;

void setup(void) 
{
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
  
  drawHealth();
  drawMana();
  
  bmpDraw(images[0], 110, 378);
}

void loop() 
{
  
      // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) 
  {
    curX = p.x;
    
    if(curX - lastX > distX)
    {
      lastX = curX;
      bmpDraw(images[1], 110, 378);
    }
    
    if(curX - lastX < -distX)
    {
      lastX = curX;
      bmpDraw(images[0], 110, 378);
    }
  }
  
}

void drawHealth()
{
  tft.drawRect(10, 10, 300, 25, 0x0000);
  tft.fillRect(11, 11, 298, 23, 0xF800);
}

void drawMana()
{
  tft.drawRect(10, 36, 300, 25, 0x0000);
  tft.fillRect(11, 37, 298, 23, 0x001F);
}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint16_t y) 
{

  File     bmpFile = SD.open(filename);
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) 
    return;

  //Serial.println();
  //Serial.print(F("Loading image '"));
  //Serial.print(filename);
  //Serial.println('\'');

  // Open requested file on SD card
  //bmpFile = SD.open(filename);
//  if ((bmpFile = SD.open(filename)) == NULL) 
//  {
//    Serial.print(F("File not found"));
//    return;
//  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) 
  { 
    // BMP signature
    //Serial.print(F("File size: ")); 
    Serial.println(read32(bmpFile));
    
    (void)read32(bmpFile); // Read & ignore creator bytes
    
    bmpImageoffset = read32(bmpFile); // Start of image data
    
    //Serial.print(F("Image Offset: ")); 
    Serial.println(bmpImageoffset, DEC);
    
    // Read DIB header
    //Serial.print(F("Header size: ")); 
    Serial.println(read32(bmpFile));
    
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    
    if(read16(bmpFile) == 1) 
    { 
      // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      
      //Serial.print(F("Bit Depth: ")); 
      Serial.println(bmpDepth);
      
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) 
      { 
        // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        //Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
       // Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) 
        {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) 
        { 
          // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          
          if(flip) 
          // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     
          // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
            
          if(bmpFile.position() != pos) 
          { 
            // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) 
          { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) 
            { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          } // end pixel
        } // end scanline
        
        //Serial.print(F("Loaded in "));
        //Serial.print(millis() - startTime);
        //Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  Serial.flush();
//  if(!goodBmp)
//    Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) 
{
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) 
{
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}