#include "lora.h"

RH_RF95 rf95(PIN_SPI_SS, RFM95_INT);
uint8_t rf95_buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t rf95_buf_len = sizeof(rf95_buf);

void LoRa::setup()
{
    Serial.print("Setting up LoRa radio module... ");
    pinMode(RFM95_LED, OUTPUT);
    pinMode(RFM95_RST, OUTPUT);

    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    while (!rf95.init())
    {
        Serial.println(" failed");
        while (1)
            ;
    }

    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ))
    {
        Serial.println("setFrequency failed");
        while (1)
            ;
    }

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
    // you can set transmitter powers from 5 to 23 dBm
    rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096);
    rf95.setTxPower(18);
    Serial.println("done");
}

std::string LoRa::receive()
{
    if (!rf95.available())
    {
        delay(100);
        return "";
    }

    if (!rf95.recv(rf95_buf, &rf95_buf_len))
    {
        Serial.println("LoRa - No message received");
        return "";
    }

    Serial.print("LoRa - Message received: ");
    Serial.println((char *)rf95_buf);

    digitalWrite(RFM95_LED, HIGH);
    delay(100);
    digitalWrite(RFM95_LED, LOW);

    return std::string((char *)rf95_buf);
}

void LoRa::send(std::string &message)
{
    const uint8_t messageLength = message.length() + 1;
    assert(messageLength <= 256);

    rf95.send((uint8_t *)message.c_str(), messageLength);
    rf95.waitPacketSent();
    Serial.print("LoRa - Message sent: ");
    Serial.println(message.c_str());

    digitalWrite(RFM95_LED, HIGH);
    delay(100);
    digitalWrite(RFM95_LED, LOW);
}
