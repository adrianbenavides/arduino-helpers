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

void LoRa::receive()
{
    if (!rf95.available()) {
        delay(100);
        return;
    }

    if (!rf95.recv(rf95_buf, &rf95_buf_len)) {
        Serial.println("LoRa - Anything received");
        return;
    }

    digitalWrite(RFM95_LED, HIGH);

    Serial.print("LoRa - Package received: ");
    Serial.println((char *)rf95_buf);

    digitalWrite(RFM95_LED, LOW);
}

void LoRa::send()
{
    uint8_t input[] = "message, hola: this is Anu"; // Up to 255 chars
    digitalWrite(RFM95_LED, HIGH);

    rf95.send(input, sizeof(input) + 1);
    rf95.waitPacketSent();
    Serial.print("LoRa - Package sent: ");
    Serial.println((char *)input);

    digitalWrite(RFM95_LED, LOW);
}
