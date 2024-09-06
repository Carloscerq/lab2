#include "eventHandler.h"
#include "data.h"

void handleClick(struct globalStatus *data, int buttnEvent, int bttn) {    
    if (buttnEvent == BUTTON_NOT_PRESSED && data->btnPrevState[bttn] == IS_ON) {
        data->btnPrevState[bttn] = IS_OFF;
        return;
    }

    if (
            buttnEvent == BUTTON_PRESSED &&
            data->btnPrevState[bttn] == IS_OFF &&
            data->ledState[bttn] == IS_ON &&
            data->shouldBeep[0] == IS_OFF
        ) {
        data->ledState[bttn] = IS_OFF;
        data->btnPrevState[bttn] = IS_ON;
        return;
    }
    
    if (
            buttnEvent == BUTTON_PRESSED &&
            data->btnPrevState[bttn] == IS_OFF &&
            data->ledState[bttn] == IS_OFF
       ) {
        data->ledState[bttn] = IS_ON;
        data->shouldBeep[0] = IS_ON;
        data->btnPrevState[bttn] = IS_ON;
        return;
    }

}

void handleADC(struct globalStatus *data, unsigned int adc_value) {
    if (adc_value >= VOLTAGE_THRESHOLD && data->adcPrevState == IS_OFF) {
        data->ledState[2] = IS_ON;
        data->shouldBeep[1] = IS_ON;
        data->adcPrevState == IS_ON;
        return;
    }
    
    if(adc_value < VOLTAGE_THRESHOLD && data->adcPrevState == IS_ON){
        data->ledState[2] = IS_OFF;
        data->shouldBeep[1] = IS_OFF;
        data->adcPrevState == IS_OFF;
        return;
    }
}

void disableAlarm(struct globalStatus *data, int buttnEvent) {
    if (buttnEvent == 0) {
        data->shouldBeep[0] = IS_OFF;        
        data->shouldBeep[1] = IS_OFF;
    }
}