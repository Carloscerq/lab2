#include "cc1101.h"
#include "spi.h"
#include <xc.h>

#define LED LATCbits.LATC7
#define GDO0 PORTCbits.RC0

uint8_t txBuffer[BUF_SIZE];
uint8_t rxBuffer[BUF_SIZE];
uint8_t rxPacketLen = 0;

void cc1101_init(void) {
    spi_init();
    spi_strobe(CCxxx0_SRES); // Reset CC1101
    while (GDO0); // Wait until GDO0 goes low
    cc1101_write_rf_settings();
}

void cc1101_write_rf_settings(void) {
    // Add your specific RF settings here
    spi_write_reg(CCxxx0_IOCFG2, 0x29); // GDO2 output pin configuration
    spi_write_reg(CCxxx0_IOCFG0, 0x06); // GDO0 output pin configuration
    spi_write_reg(CCxxx0_FIFOTHR, 0x07); // RX FIFO and TX FIFO thresholds
    spi_write_reg(CCxxx0_PKTLEN, 0xFF); // Packet length
    spi_write_reg(CCxxx0_PKTCTRL1, 0x04); // Packet automation control
    spi_write_reg(CCxxx0_PKTCTRL0, 0x05); // Packet automation control
    // Add more settings as needed
}

void cc1101_send_packet(uint8_t size) {
    spi_write_burst_reg(CCxxx0_TXFIFO, txBuffer, size);
    spi_strobe(CCxxx0_STX); // Start transmission
    while (!GDO0); // Wait for GDO0 to go high
    while (GDO0); // Wait for GDO0 to go low again
}

uint8_t cc1101_receive_packet(void) {
    if (spi_read_status(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO) {
        rxPacketLen = spi_read_reg(CCxxx0_RXFIFO);
        spi_read_burst_reg(CCxxx0_RXFIFO, rxBuffer, rxPacketLen);
        if (spi_read_reg(CCxxx0_PKTSTATUS) & CRC_OK) {
            return 1;
        }
    }
    return 0;
}
