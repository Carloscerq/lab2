#ifndef GPIO_H
#define GPIO_H

#include <xc.h>
#include <stdint.h>

// Definições de pinos e portas

#define DC_PIN       LATGbits.LATG12
#define DC_TRIS      TRISGbits.TRISG12

#define RST_PIN      LATGbits.LATG13
#define RST_TRIS     TRISGbits.TRISG13

#define CS_PIN       LATGbits.LATG14
#define CS_TRIS      TRISGbits.TRISG14

// Macros para configurar os pinos
#define DC_Set()   (DC_PIN = 1)
#define DC_Clear() (DC_PIN = 0)

#define RST_Set()  (RST_PIN = 1)
#define RST_Clear()(RST_PIN = 0)

#define CS_Set()   (CS_PIN = 1)
#define CS_Clear() (CS_PIN = 0)

// Função de inicialização dos GPIOs
void GPIO_Init(void);

#endif // GPIO_H
