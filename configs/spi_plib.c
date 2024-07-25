#include "spi_plib.h"
#include "system.h"

// Inicializa o SPI como mestre
void SPI_InitMaster(uint8_t spiChannel, uint32_t baudRate) {
//    SYSTEMConfigWaitStatesAndPB(fpb);
//    CheKseg0CacheOn();
//    mBMXDisableDRMWaitState();

    SpiChnOpen(spiChannel, SPICON_MSTEN | SPICON_FRMEN | SPICON_SMP | SPICON_ON, baudRate);
}

// Envia dados pelo SPI
void SPI_SendData(uint8_t spiChannel, const char* txBuff, size_t txSize) {
    while (txSize--) {
        SpiChnPutC(spiChannel, *txBuff++);
    }
}

// Recebe dados pelo SPI
void SPI_ReceiveData(uint8_t spiChannel, char* rxBuff, size_t rxSize) {
    while (rxSize--) {
        *rxBuff++ = SpiChnGetC(spiChannel);
    }
}

// Realiza a transferência de dados
void SPI_TransferData(uint8_t spiChannel, const char* txBuff, char* rxBuff, size_t txSize) {
    int ix = txSize;
    const char* pSrc = txBuff;
    char* pDst = rxBuff;

    while (ix--) {
        SpiChnPutC(spiChannel, *pSrc++);  // Envia dados pelo canal mestre
        *pDst++ = SpiChnGetC(spiChannel); // Recebe dados pelo canal mestre
    }
}
