#ifndef SPI_PLIB_H
#define SPI_PLIB_H

#include <stdint.h>
#include <stddef.h>

// Funções de inicialização do SPI
void SPI_InitMaster(uint8_t spiChannel);

// Funções de transmissão e recepção de dados
void SPI_SendByte(uint8_t spiChannel, uint8_t txByte);
uint8_t SPI_ReceiveByte(uint8_t spiChannel);
uint8_t SPI_TransferByte(uint8_t spiChannel, uint8_t txByte);

#endif // SPI_PLIB_H
