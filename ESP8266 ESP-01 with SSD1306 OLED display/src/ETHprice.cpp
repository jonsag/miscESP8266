
#include <Arduino.h>

#include "secrets.h"

#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <time.h>

#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// SSL certificate of cryptocompare.com
const char digicert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIEADCCAuigAwIBAgIBADANBgkqhkiG9w0BAQUFADBjMQswCQYDVQQGEwJVUzEh
MB8GA1UEChMYVGhlIEdvIERhZGR5IEdyb3VwLCBJbmMuMTEwLwYDVQQLEyhHbyBE
YWRkeSBDbGFzcyAyIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MB4XDTA0MDYyOTE3
MDYyMFoXDTM0MDYyOTE3MDYyMFowYzELMAkGA1UEBhMCVVMxITAfBgNVBAoTGFRo
ZSBHbyBEYWRkeSBHcm91cCwgSW5jLjExMC8GA1UECxMoR28gRGFkZHkgQ2xhc3Mg
MiBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTCCASAwDQYJKoZIhvcNAQEBBQADggEN
ADCCAQgCggEBAN6d1+pXGEmhW+vXX0iG6r7d/+TvZxz0ZWizV3GgXne77ZtJ6XCA
PVYYYwhv2vLM0D9/AlQiVBDYsoHUwHU9S3/Hd8M+eKsaA7Ugay9qK7HFiH7Eux6w
wdhFJ2+qN1j3hybX2C32qRe3H3I2TqYXP2WYktsqbl2i/ojgC95/5Y0V4evLOtXi
EqITLdiOr18SPaAIBQi2XKVlOARFmR6jYGB0xUGlcmIbYsUfb18aQr4CUWWoriMY
avx4A6lNf4DD+qta/KFApMoZFv6yyO9ecw3ud72a9nmYvLEHZ6IVDd2gWMZEewo+
YihfukEHU1jPEX44dMX4/7VpkI+EdOqXG68CAQOjgcAwgb0wHQYDVR0OBBYEFNLE
sNKR1EwRcbNhyz2h/t2oatTjMIGNBgNVHSMEgYUwgYKAFNLEsNKR1EwRcbNhyz2h
/t2oatTjoWekZTBjMQswCQYDVQQGEwJVUzEhMB8GA1UEChMYVGhlIEdvIERhZGR5
IEdyb3VwLCBJbmMuMTEwLwYDVQQLEyhHbyBEYWRkeSBDbGFzcyAyIENlcnRpZmlj
YXRpb24gQXV0aG9yaXR5ggEAMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQAD
ggEBADJL87LKPpH8EsahB4yOd6AzBhRckB4Y9wimPQoZ+YeAEW5p5JYXMP80kWNy
OO7MHAGjHZQopDH2esRU1/blMVgDoszOYtuURXO1v0XJJLXVggKtI3lpjbi2Tc7P
TMozI+gciKqdi0FuFskg5YmezTvacPd+mSYgFFQlq25zheabIZ0KbIIOqPjCDPoQ
HmyW74cNxA9hi63ugyuV+I6ShHI56yDqg+2DzZduCLzrTia2cyvk0/ZM/iZx4mER
dEr/VxqHD3VILs9RaRegAhJhldXRQLIQTO7ErBBDpqWeCtWVYpoNz4iCxTIM5Cuf
ReYNnyicsbkqWletNw+vHX/bvZ8=
-----END CERTIFICATE-----
)EOF";

HTTPClient https;

#define LOGO_WIDTH 23
#define LOGO_HEIGHT 38

const char *apiURL = "https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD";
// ETH logo

const unsigned char eth[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00,
    0xfc, 0x00, 0x01, 0xfe, 0x00, 0x01, 0xfe, 0x00, 0x03, 0xff, 0x00, 0x03, 0xff, 0x00, 0x07, 0xff,
    0x80, 0x0f, 0xff, 0xc0, 0x0f, 0xff, 0xc0, 0x1f, 0xff, 0xe0, 0x1f, 0xff, 0xe0, 0x3f, 0xff, 0xf0,
    0x3f, 0xff, 0xf0, 0x7f, 0xff, 0xf8, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xf8, 0x1f, 0xff, 0xe0, 0x07,
    0xff, 0x80, 0x43, 0xff, 0x08, 0x60, 0xfc, 0x18, 0x38, 0x78, 0x70, 0x1c, 0x00, 0xe0, 0x1f, 0x03,
    0xe0, 0x0f, 0xcf, 0xc0, 0x07, 0xff, 0x80, 0x03, 0xff, 0x00, 0x03, 0xff, 0x00, 0x01, 0xfe, 0x00,
    0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x78, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00,
    0x00, 0x00};

void resetDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void print(char *str)
{
    Serial.print(str);
    display.write(str);
    display.display();
}

void println(const char *str)
{
    Serial.println(str);
    display.println(str);
    display.display();
}

void setClock() // Set time via NTP, as required for x.509 validation
{
    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    resetDisplay();
    println("NTP time sync: ");

    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
        print(".");
        now = time(nullptr);
    }

    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    resetDisplay();
    println("Current time: ");
    println(asctime(&timeinfo));

    delay(2000);
}

void drawCentreString(const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
    Serial.print(buf);
    display.display();
}

void printBTCLogo()
{
    display.drawBitmap(
        (display.width() - LOGO_WIDTH) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        eth, LOGO_WIDTH, LOGO_HEIGHT, 1);
}

void fetchURL(BearSSL::WiFiClientSecure *client)
{
    resetDisplay();

    if (https.begin(*client, apiURL))
    {
        println("Obtaining price...");

        // start connection and send HTTP header
        int httpCode = https.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = https.getString();
                Serial.println(payload);

                StaticJsonDocument<200> doc;
                deserializeJson(doc, payload);
                String price = doc["USD"];
                resetDisplay();
                printBTCLogo();
                drawCentreString(price.c_str(), 64, 55);
                display.display();
            }
        }
        else
        {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            display.println(sprintf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str()));
            display.display();
        }
        https.end();
    }
    else
    {
        println("[HTTPS] Unable to connect");
    }
}

void connect()
{
    BearSSL::WiFiClientSecure client;
    BearSSL::X509List cert(digicert);
    client.setTrustAnchors(&cert);
    setClock();
    fetchURL(&client);
}

void setup()
{
    Serial.begin(115200);
    Wire.pins(2, 0);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
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
    println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
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
