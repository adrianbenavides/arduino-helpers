#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <assert.h>

class NodeMcu
{
public:
    NodeMcu();
    NodeMcu(std::string &settings);

    uint deviceId;
    void setupWithWiFi();
    void setupWithoutWiFi();

private:
    std::string settings;
    uint port;
    const char *ssid;
    const char *password;

    void init();
    void setupFilesystem();
    void deserializeSettings();
    void enableWiFi();
    void disableWiFi();
};
