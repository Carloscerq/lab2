#include "spi_data.h"

void initialize_spi(
        SPIConfig *config,
        uint32_t baudRate,
        uint8_t clockPolarity,
        uint8_t clockEdge,
        uint8_t samplePhase,
        uint8_t dataMode) {
    // Disable the SPI module
    *(config->spiCON) &= ~(1 << 15);

    // Clear the receive buffer
    while (*(config->spiSTAT) & (1 << 0)) {
        volatile uint32_t rData = *(config->spiBUF);
    }

    // Set the baud rate
    *(config->spiBRG) = (80000000 / (2 * baudRate)) - 1;

    // Set up the control register
    *(config->spiCON) = (clockPolarity << 6) |
            (clockEdge << 8) |
            (samplePhase << 9) |
            (dataMode << 10) |
            (1 << 5); // Master mode

    // Set up the pins (TRIS registers)
    // Set SDI as input
    *(config->sdiTris) |= config->sdiMask;
    // Set SDO as output
    *(config->sdoTris) &= ~config->sdoMask;
    // Set SCK as output
    *(config->sckTris) &= ~config->sckMask;
    // Set SS as output (if used)
    if (config->ssTris != NULL) {
        *(config->ssTris) &= ~config->ssMask;
    }

    // Enable the SPI module
    *(config->spiCON) |= (1 << 15);
}

void send_data_via_spi(uint8_t data, SPIConfig * config) {
    // Write data to the buffer
    *(config->spiBUF) = data;
    // Wait until the transfer is complete
    while (!(*(config->spiSTAT) & (1 << 0)));
    // Read and return the received data
    return *(config->spiBUF);
}
