#include "spi.h"
#include <xc.h>

#define MOSI LATCbits.LATC5
#define MISO PORTCbits.RC4
#define SCK  LATCbits.LATC3
#define CS   LATCbits.LATC1

void spi_init(void) {
    TRISCbits.TRISC5 = 0; // MOSI as output
    TRISCbits.TRISC4 = 1; // MISO as input
    TRISCbits.TRISC3 = 0; // SCK as output
    TRISCbits.TRISC1 = 0; // CS as output

    CS = 1;
    SCK = 0;
    MOSI = 0;
}

//Configure the CC1101 module by reading or writing to configuration
//register through SPI interface. SPI serial interface consists of four lines:
//MOSI: Master Output Slave Input (master write)
//MISO: Master Input Slave Output (master read)
//SCK: Serial clock signal, controlled by master
//CSN: chip select signal, low active
// <SPI write and read Code>
uint8_t spi_tx_rx_byte(uint8_t data) {
    uint8_t i, temp = 0;
    SCK = 0;
    for (i = 0; i < 8; i++) {
        if (data & 0x80) MOSI = 1;
        else MOSI = 0;
        data <<= 1;
        __delay_us(1);
        SCK = 1;
        temp <<= 1;
        if (MISO) temp++;
        __delay_us(1);
        SCK = 0;
    }
    return temp;
}

/////////////////////////////

// Configure the CC1101 module through the SPI interface, reading and writing
//into configuration register>
uint8_t spi_read_reg(uint8_t addr) {
    uint8_t temp, value;
    temp = addr | READ_SINGLE;
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(temp);
    value = spi_tx_rx_byte(0);
    CS = 1;
    return value;
}

/////////////////////////////

void spi_write_reg(uint8_t addr, uint8_t value) {
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(addr);
    spi_tx_rx_byte(value);
    CS = 1;
}

/////////////////////////////

void spi_write_burst_reg(uint8_t addr, uint8_t* buffer, uint8_t count) {
    uint8_t i;
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(addr | WRITE_BURST);
    for (i = 0; i < count; i++) {
        spi_tx_rx_byte(buffer[i]);
    }
    CS = 1;
}

////////////////////////////////

void spi_read_burst_reg(uint8_t addr, uint8_t* buffer, uint8_t count) {
    uint8_t i;
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(addr | READ_BURST);
    for (i = 0; i < count; i++) {
        buffer[i] = spi_tx_rx_byte(0);
    }
    CS = 1;
}

/////////////////////////////

void spi_strobe(uint8_t strobe) {
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(strobe);
    CS = 1;
}

/////////////////////////////

uint8_t spi_read_status(uint8_t addr) {
    uint8_t x;
    CS = 0;
    while (MISO);
    spi_tx_rx_byte(addr | READ_BURST);
    x = spi_tx_rx_byte(0);
    CS = 1;
    return x;
}
