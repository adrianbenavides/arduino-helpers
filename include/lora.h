#include <RH_RF95.h>

#define RFM95_RST D0 // RST
#define RFM95_INT D1 // DIO0
#define RFM95_LED D2

// PIN_SPI_SCK  (14) -> D5
// PIN_SPI_MISO (12) -> D6
// PIN_SPI_MOSI (13) -> D7
// PIN_SPI_SS   (15) -> D8

// Must match RX's freq
#define RF95_FREQ 434.0

class LoRa
{
public:
    void setup();
    void receive();
    void send();
};
