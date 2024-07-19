#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// Define read and write modes
#define WRITE_BURST     0x40
#define READ_SINGLE     0x80
#define READ_BURST      0xC0

void spi_init(void);
uint8_t spi_tx_rx_byte(uint8_t data);
void spi_write_reg(uint8_t addr, uint8_t value);
uint8_t spi_read_reg(uint8_t addr);
void spi_write_burst_reg(uint8_t addr, uint8_t* buffer, uint8_t count);
void spi_read_burst_reg(uint8_t addr, uint8_t* buffer, uint8_t count);
void spi_strobe(uint8_t strobe);
uint8_t spi_read_status(uint8_t addr);

#endif // SPI_H
