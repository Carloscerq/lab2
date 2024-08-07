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
            data->shouldBeep == IS_OFF
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
        data->shouldBeep = IS_ON;
        data->btnPrevState[bttn] = IS_ON;
        return;
    }

}

void disableAlarm(struct globalStatus *data, int buttnEvent) {
    if (buttnEvent == 0) {
        data->shouldBeep = IS_OFF;
    }
}