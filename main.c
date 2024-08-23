// TODO See if we can import bool
#include <xc.h>
#include "configs/system.h"
#include "configs/gpio.h"
#include "data.h"
#include "eventHandler.h"
#include "app.h"
#include "ili9341.h"

int main()
{
    SystemInitialize();
    //APP_Initialize();
    ILI9341_Init();
    
    ILI9341_FillScreen(ILI9341_GREEN);
    
    struct globalStatus applicationStatus;
    applicationStatus.ledState[0] = IS_OFF;
    applicationStatus.ledState[1] = IS_OFF;
    applicationStatus.btnPrevState[0] = IS_OFF;
    applicationStatus.btnPrevState[1] = IS_OFF;
    applicationStatus.shouldBeep = IS_OFF;
    
    TestPLIB();
    
    while(1)
    {
        handleClick(&applicationStatus, BUTTON_PROB1_PIN, BUTTON_ONE);
        handleClick(&applicationStatus, BUTTON_PROB2_PIN, BUTTON_TWO);
        
        disableAlarm(&applicationStatus, BUTTON_ALARM_PIN);        
        
        BUZZER_PIN = applicationStatus.shouldBeep;
        LED1_PIN = applicationStatus.ledState[0];
        LED2_PIN = applicationStatus.ledState[1];
    } // main loop
} // main