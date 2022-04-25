#include <Arduino.h>

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include "config.h"
#include "tests.h"

void setup()
{
  //Serial.begin(9600);

  Wire.begin(SDA, SCL);

  //Serial.println("Starting display ...");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // init done

  // Wire.setClock(400000L);   // uncomment this to set I2C clock to 400kHz

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //Serial.println("Splash screen ...");
  display.display();
  delay(2000);

  // Clear the buffer.
  //Serial.println("Clear display ...");
  display.clearDisplay();

  // draw a single pixel
  //Serial.println("Test 1/15: single pixel ...");
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw many lines
  //Serial.println("Test 2/15: lines ...");
  testdrawline();
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw rectangles
  //Serial.println("Test 3/15: rectangles ...");
  testdrawrect();
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw multiple rectangles
  //Serial.println("Test 4/15: rectangles ...");
  testfillrect();
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw multiple circles
  //Serial.println("Test 5/15: circles ...");
  testdrawcircle();
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw a white circle, 10 pixel radius
  //Serial.println("Test 6/15: fill circle ...");
  display.fillCircle(display.width() / 2, display.height() / 2, 10, WHITE);
  display.display();
  delay(2000);

  display.clearDisplay();

  //Serial.println("Test 7/15: round rectangle ...");
  testdrawroundrect();
  delay(2000);

  display.clearDisplay();

  //Serial.println("Test 8/15: fill round rectangle ...");
  testfillroundrect();
  delay(2000);

  display.clearDisplay();

  //Serial.println("Test 9/15: triangle ...");
  testdrawtriangle();
  delay(2000);

  display.clearDisplay();

  //Serial.println("Test 10/15: fill triangle ...");
  testfilltriangle();
  delay(2000);

  display.clearDisplay();

  // draw the first ~12 characters in the font
  //Serial.println("Test 10/15: characters ...");
  testdrawchar();
  display.display();
  delay(2000);

  display.clearDisplay();

  // draw scrolling text
  //Serial.println("Test 11/15: scroll text ...");
  testscrolltext();
  delay(2000);

  display.clearDisplay();

  // text display tests
  //Serial.println("Test 12/15: text ...");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x");
  display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);

  display.clearDisplay();

  // miniature bitmap display
  //Serial.println("Test 13/15: bitmap ...");
  display.drawBitmap(30, 16, logo16_glcd_bmp, 16, 16, 1);
  display.display();
  delay(1);

  // invert the display
  //Serial.println("Test 14/15: invert ...");
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  display.clearDisplay();

  // draw a bitmap icon and 'animate' movement
  //Serial.println("Test 15/15: animate ...");
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}

void loop()
{
}
