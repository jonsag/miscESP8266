
// set I2C pins (SDA = GPIO2, SCL = GPIO0), default clock is 100kHz
#define SDA 2
#define SCL 0

/*
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define OLED_RESET 1 // define SSD1306 OLED reset (TX pin)

Adafruit_SSD1306 display(OLED_RESET);
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10

#define XPOS 0
#define YPOS 1

#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
    {B00000000, B11000000,
     B00000001, B11000000,
     B00000001, B11000000,
     B00000011, B11100000,
     B11110011, B11100000,
     B11111110, B11111000,
     B01111110, B11111111,
     B00110011, B10011111,
     B00011111, B11111100,
     B00001101, B01110000,
     B00011011, B10100000,
     B00111111, B11100000,
     B00111111, B11110000,
     B01111100, B11110000,
     B01110000, B01110000,
     B00000000, B00110000};

/*
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
*/