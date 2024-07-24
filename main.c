#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

// TODO See if we can import bool
#include <xc.h>
#include <plib.h>
#include "data.h"
#include "eventHandler.h"
#include "app.h"

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

#define SYS_FREQ        (80000000L)  // System frequency
#define SPI_BAUD_RATE   1000000      // Desired SPI Baud Rate

// Delay function using Timer1
void delay_ms(unsigned int ms) {
    while (ms--) {
        WriteTimer1(0); // Reset Timer1 count
        while (ReadTimer1() < (SYS_FREQ / 256 / 1000)); // Wait for 1 ms
    }
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