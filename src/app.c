/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <limits.h>
#include "app.h"
#include "ili9341.h"
#include "tft_gfx.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/


APP_DATA appData;

char buffer[20];

void testCircles(uint8_t radius, uint16_t color);
void testFastLines(uint16_t color1, uint16_t color2);
void testFillScreen(void);
void testFilledCircles(uint8_t radius, uint16_t color);
void testFilledRects(uint16_t color1, uint16_t color2);
void testFilledRoundRects(void);
void testRoundRects(void);
void testFilledTriangles(void);
void testLines(uint16_t color);
void testRects(uint16_t color);
void testRoundRects(void);
void testText(void);
void testTriangles(void);

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;

    unsigned char rotation;

    while (1)
    {
        ILI9341_SetRotation(0);
        ILI9341_FillScreen(ILI9341_BLACK);
        ILI9341_SetCursor(0, 0);
        ILI9341_SetTextColor(ILI9341_WHITE);
        ILI9341_SetTextSize(3);
        ILI9341_WriteString("Start...");
        CORETIMER_DelayMs(3000);

        ILI9341_FillScreen(ILI9341_RED);
  
        ILI9341_FillScreen(ILI9341_GREEN);
        ILI9341_FillScreen(ILI9341_CYAN);
        ILI9341_FillScreen(ILI9341_MAGENTA);
        ILI9341_FillScreen(ILI9341_YELLOW);

        ILI9341_FillScreen(ILI9341_WHITE);
        ILI9341_FillScreen(ILI9341_RED);
        ILI9341_FillScreen(ILI9341_GREEN);
        ILI9341_FillScreen(ILI9341_CYAN);
        ILI9341_FillScreen(ILI9341_MAGENTA);

        ILI9341_FillScreen(ILI9341_YELLOW);
        ILI9341_FillScreen(ILI9341_WHITE);
        ILI9341_FillScreen(ILI9341_RED);
        ILI9341_FillScreen(ILI9341_GREEN);
        ILI9341_FillScreen(ILI9341_CYAN);

        ILI9341_FillScreen(ILI9341_MAGENTA);
        ILI9341_FillScreen(ILI9341_YELLOW);
        ILI9341_FillScreen(ILI9341_WHITE);
        ILI9341_FillScreen(ILI9341_RED);
        ILI9341_FillScreen(ILI9341_GREEN);

        ILI9341_FillScreen(ILI9341_CYAN);
        ILI9341_FillScreen(ILI9341_MAGENTA);
        ILI9341_FillScreen(ILI9341_YELLOW);
        ILI9341_FillScreen(ILI9341_WHITE);
        ILI9341_FillScreen(ILI9341_RED);

        ILI9341_FillScreen(ILI9341_GREEN);
        ILI9341_FillScreen(ILI9341_CYAN);
        ILI9341_FillScreen(ILI9341_MAGENTA);
        ILI9341_FillScreen(ILI9341_YELLOW);
        ILI9341_FillScreen(ILI9341_WHITE);
        
        CORETIMER_DelayMs(1000);
  
        testFillScreen();
        testText();
        testLines(ILI9341_CYAN);
        testFastLines(ILI9341_RED, ILI9341_BLUE);
        testRects(ILI9341_GREEN);
        testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);
        testFilledCircles(10, ILI9341_MAGENTA);
        testCircles(10, ILI9341_WHITE);
        testTriangles();
        testFilledTriangles();
        testRoundRects();
        testFilledRoundRects();
        
        CORETIMER_DelayMs(1000);

        ILI9341_FillScreen(ILI9341_BLACK);
        CORETIMER_DelayMs(1000);
  
        uint16_t delay = 1000;
        bool isDown = true;
        uint8_t cnt = 0;
        bool isFinish = false;
    
        while (1)
        {
            for(rotation=0; rotation<4; rotation++)
            {
                ILI9341_SetRotation(rotation);
                testText();
                CORETIMER_DelayMs(delay);
      
                if (isDown)
                {
                    if (delay > 10) delay -= 50;
                    else
                    {
                        cnt++;
                        if (cnt > 50)
                        {
                            cnt = 0;
                            isDown = false;
                        }    
                    }
                }    
                else
                {    
                    if (delay < 1000) delay += 50;
                    else    //isDown = true;
                    {
                        isFinish = true;
                        break;
                    }    
                }  
            }
        
            if (isFinish)
            {
                CORETIMER_DelayMs(2000);
                break;
            }    
        }
    }

    appData.state = APP_STATE_INIT;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {
            ILI9341_FillScreen(ILI9341_BLACK);
            
            appData.state = APP_STATE_IDLE;
            break;
        }    
        case APP_STATE_IDLE:
        {
            
            break;
        }    
    }
}

/*******************************************************************************
 End of File
 */

void testFillScreen(void)
{
    ILI9341_FillScreen(ILI9341_BLACK);
    ILI9341_FillScreen(ILI9341_RED);
    ILI9341_FillScreen(ILI9341_GREEN);
    ILI9341_FillScreen(ILI9341_BLUE);
    ILI9341_FillScreen(ILI9341_BLACK);
}

void testText(void)
{
    ILI9341_FillScreen(ILI9341_BLACK);
    ILI9341_SetCursor(0, 0);
    ILI9341_SetTextColor(ILI9341_WHITE);
    ILI9341_SetTextSize(1);
    ILI9341_WriteString("Hello World!\n");
    ILI9341_SetTextColor(ILI9341_YELLOW);
    ILI9341_SetTextSize(2);
    sprintf(buffer,"%.2f\n", 1234.56);
    ILI9341_WriteString(buffer);
    ILI9341_SetTextColor(ILI9341_RED);
    ILI9341_SetTextSize(3);
    ILI9341_WriteString("DEADBEEF\n");
    ILI9341_SetTextColor(ILI9341_GREEN);
    ILI9341_SetTextSize(5);
    ILI9341_WriteString("Groop\n");
    ILI9341_SetTextSize(2);
    ILI9341_WriteString("I implore thee\n");
    ILI9341_SetTextSize(1);

    ILI9341_WriteString("my foonting turlingdromes.\n");
    ILI9341_WriteString("And hooptiously drangle me\n");
    ILI9341_WriteString("with crinkly bindlewurdles,\n");
    ILI9341_WriteString("Or I will rend thee\n");
    ILI9341_WriteString("in the gobberwarts\n");
    ILI9341_WriteString("with my blurglecruncheon,\n");
    ILI9341_WriteString("see if I don't!\n");
}

void testLines(uint16_t color)
{
    int16_t x1, y1, x2, y2;
    int16_t w = ILI9341_GetWidth();
    int16_t h = ILI9341_GetHeight();

    ILI9341_FillScreen(ILI9341_BLACK);

    x1 = y1 = 0;
    y2 = h - 1;
    for (x2 = 0; x2 < w; x2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for (y2 = 0; y2 < h; y2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
  
    ILI9341_FillScreen(ILI9341_BLACK);

    x1 = w - 1;
    y1 = 0;
    y2 = h - 1;
    for (x2 = 0; x2 < w; x2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for (y2 = 0; y2 < h; y2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);

    ILI9341_FillScreen(ILI9341_BLACK);

    x1 = 0;
    y1 = h - 1;
    y2 = 0;
    for (x2 = 0; x2 < w; x2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for(y2 = 0; y2 < h; y2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);

    ILI9341_FillScreen(ILI9341_BLACK);

    x1 = w - 1;
    y1 = h - 1;
    y2 = 0;
    for (x2 = 0; x2 < w; x2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for(y2 = 0; y2 < h; y2 += 6) ILI9341_DrawLine(x1, y1, x2, y2, color);
}

void testFastLines(uint16_t color1, uint16_t color2)
{
    int16_t x, y, w, h;
    w = ILI9341_GetWidth();
    h = ILI9341_GetHeight();

    ILI9341_FillScreen(ILI9341_BLACK);
    for (y = 0; y < h; y += 5) ILI9341_DrawFastHLine(0, y, w, color1);
    for (x = 0; x < w; x += 5) ILI9341_DrawFastVLine(x, 0, h, color2);
}

void testRects(uint16_t color)
{
    int16_t n, i, i2,
            cx = ILI9341_GetWidth() / 2,
            cy = ILI9341_GetHeight() / 2;

    ILI9341_FillScreen(ILI9341_BLACK);
    n = min(ILI9341_GetWidth(), ILI9341_GetHeight());
    for(i = 2; i < n; i += 6)
    {
        i2 = i / 2;
        ILI9341_DrawRect(cx - i2, cy - i2, i, i, color);
    }
}

void testFilledRects(uint16_t color1, uint16_t color2)
{
    int16_t n, i, i2,
            cx = ILI9341_GetWidth() / 2 - 1,
            cy = ILI9341_GetHeight() / 2 - 1;

    ILI9341_FillScreen(ILI9341_BLACK);
    n = min(ILI9341_GetWidth(), ILI9341_GetHeight());
    for (i = n; i > 0; i -= 6)
    {
        i2 = i / 2;
        ILI9341_FillRect(cx - i2, cy - i2, i, i, color1);
        ILI9341_DrawRect(cx - i2, cy - i2, i, i, color2);
  }
}

void testFilledCircles(uint8_t radius, uint16_t color)
{
    int x, y, w = ILI9341_GetWidth(), h = ILI9341_GetHeight(), r2 = radius * 2;

    ILI9341_FillScreen(ILI9341_BLACK);
    for (x = radius; x < w; x += r2)
    {
        for (y = radius; y < h; y += r2)
        {
            ILI9341_FillCircle(x, y, radius, color);
        }
    }
}

void testCircles(uint8_t radius, uint16_t color)
{
    int16_t x, y, r2 = radius * 2,
            w = ILI9341_GetWidth() + radius,
            h = ILI9341_GetHeight() + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.
    for (x = 0; x < w; x += r2)
    {
        for (y = 0; y < h; y += r2)
        {
            ILI9341_DrawCircle(x, y, radius, color);
        }
    }
}

void testTriangles(void)
{
    int16_t n, i, cx = ILI9341_GetWidth() / 2 - 1,
            cy = ILI9341_GetHeight() / 2 - 1;

    ILI9341_FillScreen(ILI9341_BLACK);
    n = min(cx, cy);
    for (i = 0; i < n; i += 5)
    {
        ILI9341_DrawTriangle(
            cx, cy - i, // peak
            cx - i, cy + i, // bottom left
            cx + i, cy + i, // bottom right
            ILI9341_Color565(0, 0, i));
    }
}

void testFilledTriangles(void)
{
    int16_t i, cx = ILI9341_GetWidth() / 2 - 1,
            cy = ILI9341_GetHeight() / 2 - 1;

    ILI9341_FillScreen(ILI9341_BLACK);
    for (i = min(cx, cy); i > 10; i -= 5)
    {
        ILI9341_FillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, ILI9341_Color565(0, i, i));
        ILI9341_DrawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, ILI9341_Color565(i, i, 0));
    }
}

void testRoundRects(void)
{
    int16_t w, i, i2,
            cx = ILI9341_GetWidth() / 2 - 1,
            cy = ILI9341_GetHeight() / 2 - 1;

    ILI9341_FillScreen(ILI9341_BLACK);
    w = min(ILI9341_GetWidth(), ILI9341_GetHeight());
    for (i = 0; i < w; i += 6)
    {
        i2 = i / 2;
        ILI9341_DrawRoundRect(cx - i2, cy - i2, i, i, i / 8, ILI9341_Color565(i, 0, 0));
    }
}

void testFilledRoundRects(void)
{
    int16_t i, i2, cx, cy;

    cx = ILI9341_GetWidth() / 2 - 1;
    cy = ILI9341_GetHeight() / 2 - 1;

    ILI9341_FillScreen(ILI9341_BLACK);

    for (i = min(ILI9341_GetWidth(), ILI9341_GetHeight()); i > 20; i -= 6)
    {
        i2 = i / 2;
        ILI9341_FillRoundRect(cx - i2, cy - i2, i, i, i / 8, ILI9341_Color565(0, i, 0));
    }
}
