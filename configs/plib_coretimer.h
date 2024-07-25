#ifndef PLIB_CORETIMER_H    // Guards against multiple inclusion
#define PLIB_CORETIMER_H

#include <stdint.h>
#include <stdbool.h>

#define CORE_TIMER_FREQUENCY    (40000000U)
#define CORE_TIMER_COMPARE_VALUE    0x9c40

void CORETIMER_Initialize(void);
void CORETIMER_Start(void);
void CORETIMER_Stop(void);
uint32_t CORETIMER_FrequencyGet (void);
void CORETIMER_CompareSet ( uint32_t compare);
uint32_t CORETIMER_CounterGet (void);
bool CORETIMER_CompareHasExpired(void);

void CORETIMER_DelayMs (uint32_t delay_ms);
void CORETIMER_DelayUs (uint32_t delay_us);

#endif
