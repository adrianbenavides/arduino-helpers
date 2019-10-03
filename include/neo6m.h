#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define NEO6M_RX_PIN D2 // board RX D2 --> neo6m TX
#define NEO6M_TX_PIN D3 // board TX D3 --> neo6m RX
#define NEO6M_BAUD 9600 // Default baud of NEO-6M is 9600

class Neo6m
{
public:
    void setup();
    TinyGPSPlus read();
    void print(TinyGPSPlus gpsParser);
};
