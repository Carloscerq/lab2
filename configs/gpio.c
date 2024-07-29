#include "gpio.h"

void GPIO_Init(void) {
     // Configura os pinos DC, RST e CL como saídas
    DC_TRIS = 0;   // Configura RG12 como saída
    RST_TRIS = 0;   // Configura RG13 como saída
    CS_TRIS = 0;   // Configura RG14 como saída
    
    BUTTON_PROB1_TRIS = 1;
    BUTTON_PROB2_TRIS = 1;
    BUTTON_ALARM_TRIS = 1;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    BUZZER_TRIS = 0;
    
    DC_Clear();
    RST_Clear();
    CS_Clear();
    
    LED1_Clear();
    LED2_Clear();
    BUZZER_Clear();
    
}
