#include "neo6m.h"

static TinyGPSPlus gpsParser;
static TinyGPSPlus emptyGpsParser;
static SoftwareSerial gpsSerial(NEO6M_RX_PIN, NEO6M_TX_PIN);

void Neo6m::setup()
{
    Serial.print("Setting up Neo-6M GPS module... ");
    gpsSerial.begin(NEO6M_BAUD);
    Serial.println("done");
}

TinyGPSPlus Neo6m::read()
{
    while (gpsSerial.available() > 0)
        if (gpsParser.encode(gpsSerial.read()))
            return gpsParser;

    return emptyGpsParser;
}

void Neo6m::print(TinyGPSPlus gpsParser)
{
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
    if (gpsParser.date.isValid() && gpsParser.time.isValid())
    {
        Serial.printf("%d-%d-%dT%d:%d:%d+00:00\n",
                      gpsParser.date.year(),
                      gpsParser.date.month(),
                      gpsParser.date.day(),
                      gpsParser.time.hour(),
                      gpsParser.time.minute(),
                      gpsParser.time.second());
    }
    else
    {
        Serial.println("-");
    }

    Serial.print("Speed: ");
    if (gpsParser.speed.isValid())
    {
        Serial.println(gpsParser.speed.kmph());
    }
    else
    {
        Serial.println("-");
    }

    Serial.println();
    Serial.println();
}
