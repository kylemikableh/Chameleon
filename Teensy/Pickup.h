//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/6/20.
//

#ifndef CHAMELEON_PICKUP_H
#define CHAMELEON_PICKUP_H

#include "Config.h"
#include <Arduino.h>

class ADS {
private:
    listening = false;
    current_freq = 0;

    void configureADS();
    bool checkADSConfig();

public:
    ADS();
    void startListening();
    void stopListening();
    bool isListening();
    double sample();
    double getLastSample();
};

#endif //CHAMELEON_PICKUP_H
