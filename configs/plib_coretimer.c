#include "plib_coretimer.h"
#include "system.h"

static uint32_t compareValue = CORE_TIMER_COMPARE_VALUE;

void CORETIMER_Initialize( void )
{

    // Clear Core Timer
    _CP0_SET_COUNT(0);
    _CP0_SET_COMPARE(compareValue);

    // Enable Timer by clearing Disable Count (DC) bit
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() & (~_CP0_CAUSE_DC_MASK));
}

void CORETIMER_Start( void )
{
    // Disable Timer by setting Disable Count (DC) bit
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() | _CP0_CAUSE_DC_MASK);

    // Clear Compare Timer Interrupt Flag
    IFS0CLR = 0x1;

    // Clear Core Timer
    _CP0_SET_COUNT(0);

    _CP0_SET_COMPARE(compareValue);

    // Enable Timer by clearing Disable Count (DC) bit
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() & (~_CP0_CAUSE_DC_MASK));

}

void CORETIMER_Stop( void )
{
    // Disable Timer by setting Disable Count (DC) bit
    _CP0_SET_CAUSE(_CP0_GET_CAUSE() | _CP0_CAUSE_DC_MASK);
}

uint32_t CORETIMER_FrequencyGet ( void )
{
    return (CORE_TIMER_FREQUENCY);
}

void CORETIMER_CompareSet ( uint32_t compare )
{
    compareValue = compare;
    _CP0_SET_COMPARE(compareValue);
}

uint32_t CORETIMER_CounterGet ( void )
{
    uint32_t count;
    count = _CP0_GET_COUNT();
    return count;
}

bool CORETIMER_CompareHasExpired( void )
{
    bool flagStatus = false;
    if (IFS0bits.CTIF != 0U)
    {
       // Clear Compare Timer Interrupt Flag
       IFS0CLR = 0x1;
       flagStatus = true;
    }
    return flagStatus;
}

void CORETIMER_DelayMs ( uint32_t delay_ms)
{
    uint32_t startCount, endCount;

    /* Calculate the end count for the given delay */
    endCount=(CORE_TIMER_FREQUENCY / 1000U) * delay_ms;

    startCount=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT() - startCount) < endCount)
    {
        /* Wait for compare match */
    }
}

void CORETIMER_DelayUs ( uint32_t delay_us)
{
    uint32_t startCount, endCount;

    /* Calculate the end count for the given delay */
    endCount=(CORE_TIMER_FREQUENCY / 1000000U) * delay_us;

    startCount=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT() - startCount) < endCount)
    {
        /* Wait for compare match */
    }
}

