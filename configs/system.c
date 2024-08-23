#include <xc.h>
#include "system.h"
#include "spi_plib.h"
#include "plib_coretimer.h"
#include "gpio.h"

#define _SUPPRESS_PLIB_WARNING 1
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 1

#include <plib.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

// Inicializa o SPI como mestre
void SPI_InitMaster(uint8_t spiChannel) {
    SpiChnOpen(spiChannel, SPICON_MSTEN | SPICON_FRMEN | SPICON_SMP | SPICON_ON, 8);
}

// Envia um byte pelo SPI
void SPI_SendByte(uint8_t spiChannel, uint8_t txByte) {
    SpiChnPutC(spiChannel, txByte);
}

// Recebe um byte pelo SPI
uint8_t SPI_ReceiveByte(uint8_t spiChannel) {
    return SpiChnGetC(spiChannel);
}

// Realiza a transfer�ncia de um byte (envia e recebe simultaneamente)
uint8_t SPI_TransferByte(uint8_t spiChannel, uint8_t txByte) {
    SpiChnPutC(spiChannel, txByte);        // Envia um byte
    return SpiChnGetC(spiChannel);         // Recebe um byte
}

void SystemInitialize() {
    DDPCONbits.JTAGEN = 0;

//    OSCConfig(OSC_FRC, 0, 0, 0);
//    mOSCSetPBDIV(OSC_PB_DIV_4);
//    OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_1, 0);
    
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    
    GPIO_Init();
    SPI_InitMaster(SPI_CHANNEL2); // SPI para display
    CORETIMER_Initialize();
    
    CORETIMER_Start();
}

void TestPLIB() {
    // STEP 2. configure the port registers
    PORTSetPinsDigitalOut(IOPORT_F, BIT_7);
    // STEP 3. initialize the port pin states = outputs low
    mPORTFClearBits(BIT_7);
    CORETIMER_DelayMs(500);
    mPORTFSetBits(BIT_7);
}