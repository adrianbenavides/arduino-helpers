#include <RH_RF95.h>
#include <assert.h>

#define RFM95_RST D0 // RST
#define RFM95_INT D1 // DIO0
#define RFM95_LED D2

//                  NodeMcu    UNO, Nano
// -------------|------------|-----------|
// PIN_SPI_SCK  | (14) -> D5 |    D13    |
// PIN_SPI_MISO | (12) -> D6 |    D12    |
// PIN_SPI_MOSI | (13) -> D7 |    D11    |
// PIN_SPI_SS   | (15) -> D8 |    D10    |

// Must match RX's freq
#define RF95_FREQ 434.0

class LoRa
{
public:
    void setup();
    std::string receive();
    void send(std::string &message);
};
