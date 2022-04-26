
#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#include <time.h>

#include <ArduinoJson.h>

#include "secrets.h"
#include "config.h"

HTTPClient https;

#include "ETHmods.h"

void setup()
{
    Serial.begin(115200);
    Wire.begin(screenSDA,screenSCL);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        debugMessln("SSD1306 allocation failed");
        for (;;)
            ; // Don't proceed, loop forever

    }
    resetDisplay();
    display.display();
    delay(100);

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.cp437(true);                 // Use full 256 char 'Code Page 437' font

    println("Connecting to"); // We start by connecting to a WiFi network
    println(STASSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        debugMess(".");
        display.write(".");
        display.display();
    }

    resetDisplay();
    println("WiFi connected");
    println(WiFi.localIP().toString().c_str());

    delay(1000);
}

void loop()
{
    connect();
    delay(60000);
}
