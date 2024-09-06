#pragma once

struct globalStatus {
    char ledState[3];
    char shouldBeep[2];
    char adcPrevState;
    char btnPrevState[2];
};
