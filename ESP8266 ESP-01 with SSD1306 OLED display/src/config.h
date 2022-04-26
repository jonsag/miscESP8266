
#define DEBUG 1

#if DEBUG
#define debugMess(x) Serial.print(x)
#define debugMessln(x) Serial.println(x)
#else
#define debugMess(x)
#define debugMessln(x)
#endif

/*
Pins on the ESP-01
Pin         Input       Output
5   GPIO0   pulled up   OK          connected to FLASH button, boot fails if pulled LOW
2   GPIO1   TX pin      OK          HIGH at boot, debug output at boot, boot fails if pulled LOW
3   GPIO2   pulled up   OK          HIGH at boot, connected to on-board LED, boot fails if pulled LOW
7   GPIO3   OK          RX pin      HIGH at boot
*/
// set I2C pins (SDA = GPIO2, SCL = GPIO0)
#define screenSDA 2
#define screenSCL 0

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**********
 * screenTests
 **********/
/*
#define NUMFLAKES 10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

static const unsigned char PROGMEM logo_bmp[] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};
*/
/**********
 * ETHprice
 **********/

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
