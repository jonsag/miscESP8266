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

#include "secrets.h"
#include "config.h"
#include "tests.h"

void setup()
{
#if DEBUG
  Serial.begin(9600);
#endif

    debugMessln("Set up wire ...");
    Wire.pins(2, 0);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    debugMessln("SSD1306 allocation failed");
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  debugMessln("Test 1/16: splash screen ...");
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  debugMessln("Test 2/16: single pixel ...");
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  debugMessln("Test 2/16: lines ...");
  testdrawline(); // Draw many lines

  debugMessln("Test 3/16: rectangles ...");
  testdrawrect(); // Draw rectangles (outlines)

  debugMessln("Test 4/16: filled rectangles ...");
  testfillrect(); // Draw rectangles (filled)

  debugMessln("Test 5/16: circles ...");
  testdrawcircle(); // Draw circles (outlines)

  debugMessln("Test 6/16: filled circles ...");
  testfillcircle(); // Draw circles (filled)

  debugMessln("Test 7/16: rounded rectangles ...");
  testdrawroundrect(); // Draw rounded rectangles (outlines)

  debugMessln("Test 8/16: filled rounded rectangles ...");
  testfillroundrect(); // Draw rounded rectangles (filled)

  debugMessln("Test 9/16: triangles ...");
  testdrawtriangle(); // Draw triangles (outlines)

  debugMessln("Test 10/16: filled triangles ...");
  testfilltriangle(); // Draw triangles (filled)

  debugMessln("Test 11/16: characters ...");
  testdrawchar(); // Draw characters of the default font

  debugMessln("Test 12/16: stylized characters ...");
  testdrawstyles(); // Draw 'stylized' characters

  debugMessln("Test 13/16: scrolling text ...");
  testscrolltext(); // Draw scrolling text

  debugMessln("Test 14/16: bitmap ...");
  testdrawbitmap(); // Draw a small bitmap image

  // Invert and restore display, pausing in-between
  debugMessln("Test 15/16: invert and restore display ...");
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  debugMessln("Test 16/16: animate ...");
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void loop()
{
}