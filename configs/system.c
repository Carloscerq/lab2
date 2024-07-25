#include <xc.h>
#include "system.h"
#include "spi_plib.h"
#include "plib_coretimer.h"
#include "gpio.h"

#define _SUPPRESS_PLIB_WARNING 1
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 1

#include <plib.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_4

// Inicializa o SPI como mestre
void SPI_InitMaster(uint8_t spiChannel) {
    SpiChnOpen(spiChannel, SPICON_MSTEN | SPICON_FRMEN | SPICON_SMP | SPICON_ON, 4);
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

void SystemInitialize() {
    DDPCONbits.JTAGEN = 0;

    OSCConfig(OSC_FRC, 0, 0, 0);
    mOSCSetPBDIV(OSC_PB_DIV_4);
    OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_1, 0);
    SYSTEMConfigWaitStatesAndPB(SYS_FREQ);
    CheKseg0CacheOn();
    mBMXDisableDRMWaitState();
    
    GPIO_Init();
    SPI_InitMaster(SPI_CHANNEL2); // SPI para display
    CORETIMER_Initialize();
    
    CORETIMER_Start();
}