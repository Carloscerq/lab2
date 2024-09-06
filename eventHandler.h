#pragma once

#include "data.h"

#define BUTTON_ONE 0
#define BUTTON_TWO 1
#define IS_ON 1
#define IS_OFF 0
#define BUTTON_PRESSED 0
#define BUTTON_NOT_PRESSED 1
#define VOLTAGE_THRESHOLD 512


void handleClick(struct globalStatus *data, int buttnEvent, int bttn);
void handleADC(struct globalStatus *data, unsigned int adcEvent);
void disableAlarm(struct globalStatus *data, int buttnEvent);
