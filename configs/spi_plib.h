#ifndef SPI_PLIB_H
#define SPI_PLIB_H

#include <stdint.h>
#include <stddef.h>

// Fun��es de inicializa��o do SPI
void SPI_InitMaster(uint8_t spiChannel, uint32_t baudRate);

// Fun��es de transmiss�o e recep��o de dados
void SPI_SendData(uint8_t spiChannel, const char* txBuff, size_t txSize);
void SPI_ReceiveData(uint8_t spiChannel, char* rxBuff, size_t rxSize);
void SPI_TransferData(uint8_t spiChannel, const char* txBuff, char* rxBuff, size_t txSize);

#endif // SPI_PLIB_H
