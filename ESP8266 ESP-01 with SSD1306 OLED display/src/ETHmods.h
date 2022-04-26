
void resetDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void print(char *str)
{
    debugMess(str);
    display.write(str);
    display.display();
}

void println(const char *str)
{
    debugMessln(str);
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

    debugMessln("");
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
    debugMess(buf);
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
                debugMessln(payload);

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
