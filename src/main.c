/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "data.h"
#include "eventHandler.h"
#include "app.h"
#include "ili9341.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    CORETIMER_Start();
    
    ILI9341_Init();
    ILI9341_SetRotation(0);
    ILI9341_FillScreen(ILI9341_RED);
    
    //APP_Initialize();
    
    struct globalStatus applicationStatus;
    applicationStatus.ledState[0] = IS_OFF;
    applicationStatus.ledState[1] = IS_OFF;
    applicationStatus.btnPrevState[0] = IS_OFF;
    applicationStatus.btnPrevState[1] = IS_OFF;
    applicationStatus.shouldBeep = IS_OFF;
    
    while(1)
    {
        handleClick(&applicationStatus, BUTTON_PROB1_Get(), BUTTON_ONE);
        handleClick(&applicationStatus, BUTTON_PROB2_Get(), BUTTON_TWO);
        
        disableAlarm(&applicationStatus, BUTTON_ALARM_Get());        
        
        BUZZER_PIN = applicationStatus.shouldBeep;
        LED1_PIN = applicationStatus.ledState[0];
        LED2_PIN = applicationStatus.ledState[1];
    } // main loop

    /* Execution should not come here during normal operation */
    CORETIMER_Stop();
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

