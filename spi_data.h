#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct {
    volatile uint32_t *spiCON; // SPI Control register
    volatile uint32_t *spiSTAT; // SPI Status register
    volatile uint32_t *spiBUF; // SPI Buffer register
    volatile uint32_t *spiBRG; // SPI Baud Rate Generator register
    volatile uint32_t *sdiTris; // SDI TRIS register
    volatile uint32_t *sdoTris; // SDO TRIS register
    volatile uint32_t *sckTris; // SCK TRIS register
    volatile uint32_t *ssTris; // SS TRIS register (optional)
    uint32_t sdiMask; // SDI TRIS mask
    uint32_t sdoMask; // SDO TRIS mask
    uint32_t sckMask; // SCK TRIS mask
    uint32_t ssMask; // SS TRIS mask (optional)
} SPIConfig;

void initialize_spi(
        SPIConfig *config,
        uint32_t baudRate,
        uint8_t clockPolarity,
        uint8_t clockEdge,
        uint8_t samplePhase,
        uint8_t dataMode
        );
void send_data_via_spi(uint8_t data, SPIConfig *config);