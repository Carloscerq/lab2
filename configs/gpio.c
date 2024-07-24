#include "gpio.h"

void GPIO_Init(void) {
     // Configura os pinos DC, RST e CL como sa�das
    DC_TRIS = 0;   // Configura RG12 como sa�da
    RST_TRIS = 0;  // Configura RG13 como sa�da
    CS_TRIS = 0;   // Configura RG14 como sa�da
   
    DC_Clear();
    RST_Clear();
    CS_Clear();
}
