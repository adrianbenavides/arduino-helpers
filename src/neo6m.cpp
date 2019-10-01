#include "neo6m.h"

static TinyGPSPlus gpsParser;
static TinyGPSPlus emptyGpsParser;
static SoftwareSerial gpsSerial(NEO6M_RX_PIN, NEO6M_TX_PIN);

void Neo6m::setup()
{
    gpsSerial.begin(NEO6M_BAUD);
}

TinyGPSPlus Neo6m::read()
{
    while (gpsSerial.available() > 0)
        if (gpsParser.encode(gpsSerial.read()))
            return gpsParser;

    return emptyGpsParser;
}

void Neo6m::print()
{
    while (gpsSerial.available() > 0)
    {
        if (!gpsParser.encode(gpsSerial.read()))
            continue;

        if (gpsParser.location.isValid())
        {
            Serial.print("Latitude: ");
            Serial.println(gpsParser.location.lat(), 6);
            Serial.print("Longitude: ");
            Serial.println(gpsParser.location.lng(), 6);
            Serial.print("Altitude: ");
            Serial.println(gpsParser.altitude.meters());
        }
        else
        {
            Serial.println("Location: Not Available");
        }

        Serial.print("Date: ");
        if (gpsParser.date.isValid())
        {
            Serial.print(gpsParser.date.month());
            Serial.print("/");
            Serial.print(gpsParser.date.day());
            Serial.print("/");
            Serial.println(gpsParser.date.year());
        }
        else
        {
            Serial.println("Not Available");
        }

        Serial.print("Time: ");
        if (gpsParser.time.isValid())
        {
            if (gpsParser.time.hour() < 10)
                Serial.print(F("0"));
            Serial.print(gpsParser.time.hour());
            Serial.print(":");
            if (gpsParser.time.minute() < 10)
                Serial.print(F("0"));
            Serial.print(gpsParser.time.minute());
            Serial.print(":");
            if (gpsParser.time.second() < 10)
                Serial.print(F("0"));
            Serial.print(gpsParser.time.second());
            Serial.print(".");
            if (gpsParser.time.centisecond() < 10)
                Serial.print(F("0"));
            Serial.println(gpsParser.time.centisecond());
        }
        else
        {
            Serial.println("Not Available");
        }

        Serial.print("Speed: ");
        if (gpsParser.speed.isValid())
        {
            Serial.println(gpsParser.speed.value());
        }
        else
        {
            Serial.println("Not Available");
        }

        Serial.println();
        Serial.println();
    }
}
