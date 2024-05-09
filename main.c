#define _SUPPRESS_PLIB_WARNING 1

// TODO See if we can import bool
#include <xc.h>
#include <plib.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

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
    
    
    char isProblem1 = 0;
    char isProblem2 = 0;
    
    while( 1)
    {
        /*if (_RA0 == 0) {
            if (_RA4 == 0) {
                _RA4 = 1;
            } else {
                _RA4 = 0;
                isProblem1 = 1;
            }
        }
        
        if (_RA1 == 0) {
            _RA5 = ~_RA5;
            
            if (_RA5 == 1) {
                isProblem2 = 1;
            }
        }
        
        if (_RA2 == 0) {
            isProblem1 = 0;
            isProblem2 = 0;
            _RA3 = 0;
        } 
        
        if (isProblem1 == 1 || isProblem2 == 1) {
            _RA3 = 1;
        }*/
        
        if (_RA0 == 0) {
            // RA4 = LED
            // RA0 = Butao
            // RA3 = Buzina
            _RA4 = ~_RA4;
            isProblem1 = _RA4;
        }
        
        if (_RA2 == 0) {
            isProblem1 = 0;
        }
        
        _RA3 = isProblem1 || isProblem2;
    } // main loop
} // main