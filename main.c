#define _SUPPRESS_PLIB_WARNING 1

// TODO See if we can import bool
#include <xc.h>
#include <plib.h>
#include "data.h"
#include "eventHandler.h"

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initialize_spi_plib(char num) {
    // init the SPI chn 1 as master, 8 bits/character, frame master
    // divide fpb by 2 
    SpiChnOpen(num, SPICON_MSTEN|SPICON_FRMEN|SPICON_SMP|SPICON_ON, 2);
}

int send_spi_plib(char num, const char* data) {
    SpiChnPutC(num, *data++);// send data on the master channel
    return SpiChnGetC(num);// get the received data
}

main()
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