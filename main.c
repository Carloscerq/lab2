// TODO See if we can import bool
#include <xc.h>
#include "configs/system.h"
#include "configs/gpio.h"
#include "data.h"
#include "eventHandler.h"
#include "app.h"
#include "ili9341.h"

volatile unsigned int adc_value = 0;

void inicializarADC(void) {
    AD1CON1 = 0x00E0;       // Auto-convert mode
    AD1CHS = 0;       // Selecionar o pino ADC
    AD1CSSL = 0;
    AD1CON3 = 0x1F02;       // Tempo de amostragem manual
    AD1CON2 = 0;
    AD1CON1bits.ADON = 1;   // Ligar o ADC
}

int lerADC() {
    // Iniciar a amostragem e conversão do ADC
        AD1CON1bits.SAMP = 1;  // Iniciar amostragem
        CORETIMER_DelayMs(1);
        AD1CON1bits.SAMP = 0;  // Iniciar conversão

        while (!AD1CON1bits.DONE);  // Aguardar a conversão terminar
        int adc_value = ADC1BUF0;  // Ler valor ADC
        return adc_value;
}

int main()
{
    SystemInitialize();
    //APP_Initialize();
    ILI9341_Init();
    inicializarADC();
    
    ILI9341_FillScreen(ILI9341_GREEN);
    
    struct globalStatus applicationStatus;
    applicationStatus.ledState[0] = IS_OFF;
    applicationStatus.ledState[1] = IS_OFF;
    applicationStatus.ledState[2] = IS_OFF;
    applicationStatus.btnPrevState[0] = IS_OFF;
    applicationStatus.btnPrevState[1] = IS_OFF;    
    applicationStatus.adcPrevState = IS_OFF;
    applicationStatus.shouldBeep[0] = IS_OFF;    
    applicationStatus.shouldBeep[1] = IS_OFF;
    
    while(1)
    {
        adc_value = lerADC();  // Ler valor ADC.
        
        handleClick(&applicationStatus, BUTTON_PROB1_PIN, BUTTON_ONE);
        handleClick(&applicationStatus, BUTTON_PROB2_PIN, BUTTON_TWO);
        handleADC(&applicationStatus, adc_value);
        disableAlarm(&applicationStatus, BUTTON_ALARM_PIN);        
        
        BUZZER_PIN = applicationStatus.shouldBeep[0] || applicationStatus.shouldBeep[1];
        LED1_PIN = applicationStatus.ledState[0];
        LED2_PIN = applicationStatus.ledState[1];
        LED3_PIN = applicationStatus.ledState[2];    
    } // main loop
} // main