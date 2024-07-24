#include "gpio.h"

void GPIO_Init(void) {
     // Configura os pinos DC, RST e CL como saídas
    DC_TRIS = 0;   // Configura RG12 como saída
    RST_TRIS = 0;  // Configura RG13 como saída
    CS_TRIS = 0;   // Configura RG14 como saída
   
    DC_Clear();
    RST_Clear();
    CS_Clear();
}
