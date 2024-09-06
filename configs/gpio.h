#ifndef GPIO_H
#define GPIO_H

#include <xc.h>
#include <stdint.h>

// Definições de pinos e portas
//  Init port G
#define DC_PIN       LATGbits.LATG12
#define DC_TRIS      TRISGbits.TRISG12

#define RST_PIN      LATGbits.LATG13
#define RST_TRIS     TRISGbits.TRISG13

#define CS_PIN       LATGbits.LATG14
#define CS_TRIS      TRISGbits.TRISG14

// Init port A
#define BUTTON_PROB1_PIN       PORTAbits.RA0
#define BUTTON_PROB1_TRIS      TRISAbits.TRISA0

#define BUTTON_PROB2_PIN       PORTAbits.RA1
#define BUTTON_PROB2_TRIS      TRISAbits.TRISA1

#define BUTTON_ALARM_PIN       PORTAbits.RA2
#define BUTTON_ALARM_TRIS      TRISAbits.TRISA2

#define LED1_PIN               LATAbits.LATA3
#define LED1_TRIS              TRISAbits.TRISA3

#define LED2_PIN               LATAbits.LATA4
#define LED2_TRIS              TRISAbits.TRISA4

#define LED3_PIN               LATAbits.LATA5
#define LED3_TRIS              TRISAbits.TRISA5

#define BUZZER_PIN             LATAbits.LATA6
#define BUZZER_TRIS            TRISAbits.TRISA6

// Macros para configurar os pinos
#define DC_Set()   (DC_PIN = 1)
#define DC_Clear() (DC_PIN = 0)

#define RST_Set()  (RST_PIN = 1)
#define RST_Clear()(RST_PIN = 0)

#define CS_Set()   (CS_PIN = 1)
#define CS_Clear() (CS_PIN = 0)

#define LED1_Set()     (LED1_PIN = 1)
#define LED1_Clear()   (LED1_PIN = 0)

#define LED2_Set()     (LED2_PIN = 1)
#define LED2_Clear()   (LED2_PIN = 0)

#define LED3_Set()     (LED3_PIN = 1)
#define LED3_Clear()   (LED3_PIN = 0)

#define BUZZER_Set()   (BUZZER_PIN = 1)
#define BUZZER_Clear() (BUZZER_PIN = 0)

// Função de inicialização dos GPIOs
void GPIO_Init(void);

#endif // GPIO_H
