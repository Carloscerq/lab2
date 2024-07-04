#define _SUPPRESS_PLIB_WARNING 1

// TODO See if we can import bool
#include <xc.h>
#include <plib.h>
#include "data.h"
#include "eventHandler.h"

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

#define SYS_FREQ        (80000000L)  // System frequency
#define SPI_BAUD_RATE   1000000      // Desired SPI Baud Rate

#define TFT_CS     LATBbits.LATB2 // Chip Select pin
#define TFT_DC     LATBbits.LATB3 // Data/Command pin
#define TFT_RST    LATBbits.LATB4 // Reset pin

// Delay function using Timer1
void delay_ms(unsigned int ms) {
    while (ms--) {
        WriteTimer1(0); // Reset Timer1 count
        while (ReadTimer1() < (SYS_FREQ / 256 / 1000)); // Wait for 1 ms
    }
}

void SPI_Init() {
    unsigned int pbClk;
    pbClk = SYSTEMConfigPerformance(SYS_FREQ);
    unsigned int spiClk = pbClk / 2; // SPI Clock

    // Configure SPI2 settings
    SpiChnOpen(SPI_CHANNEL2,
               SPI_OPEN_MSTEN |       // Master mode
               SPI_OPEN_CKE_REV |     // Clock edge select
               SPI_OPEN_MODE8 |       // 8-bit mode
               SPI_OPEN_ON,           // Turn on SPI
               spiClk / SPI_BAUD_RATE); // Set SPI clock
}

void ILI9341_Init(void) {
    // Reset the display
    TFT_RST = 0;
    delay_ms(100);
    TFT_RST = 1;
    delay_ms(100);

    // Chip select low to start communication
    TFT_CS = 0;

    // Initialization sequence
    ILI9341_WriteCommand(0xEF);
    ILI9341_WriteData(0x03);
    ILI9341_WriteData(0x80);
    ILI9341_WriteData(0x02);

    // Add more initialization commands as needed...

    // Chip select high to end communication
    TFT_CS = 1;
}

void ILI9341_WriteCommand(uint8_t cmd) {
    TFT_DC = 0; // Command mode
    SpiChnPutC(SPI_CHANNEL2, cmd);
    while (SpiChnIsBusy(SPI_CHANNEL2));
}

void ILI9341_WriteData(uint8_t data) {
    TFT_DC = 1; // Data mode
    SpiChnPutC(SPI_CHANNEL2, data);
    while (SpiChnIsBusy(SPI_CHANNEL2));
}

int main()
{
    DDPCONbits.JTAGEN = 0;

    OSCConfig(OSC_FRC, 0, 0, 0);
    mOSCSetPBDIV(OSC_PB_DIV_4);
    OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_1, 0);

    // Init port A
    // Must set to 0 to turn on
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    
    // Set Timer1 prescaler to 1:256
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, 0xFFFF);

    // Set Timer1 interrupt priority to lowest (optional)
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);
    
    struct globalStatus applicationStatus;
    applicationStatus.ledState[0] = IS_OFF;
    applicationStatus.ledState[1] = IS_OFF;
    applicationStatus.btnPrevState[0] = IS_OFF;
    applicationStatus.btnPrevState[1] = IS_OFF;
    applicationStatus.shouldBeep = IS_OFF;
    
    while( 1)
    {
        handleClick(&applicationStatus, _RA0, BUTTON_ONE);
        handleClick(&applicationStatus, _RA1, BUTTON_TWO);
        
        disableAlarm(&applicationStatus, _RA2);        
        
        _RA3 = applicationStatus.shouldBeep;
        _RA4 = applicationStatus.ledState[0];
        _RA5 = applicationStatus.ledState[1];
    } // main loop
} // main