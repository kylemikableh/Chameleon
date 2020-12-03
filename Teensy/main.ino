//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/3/20.
//

#include "Config.h"

int index = -1;
bool header = true;
unsigned int notes[6] = [];

void setup() {
    Serial.begin(115200);
    HW_SERIAL.begin(9600);

    pinMode(STRING1_PWM, OUTPUT);
    pinMode(STRING1_DIR, OUTPUT);
}

void loop() {
    // UART from Arduino - Send string number then frequency
    if (HW_SERIAL.available() > 0) {
        int incoming = HW_SERIAL.read();
        if (header) {
            index = incoming - 1;
            header = false
        } else {
            notes[index] = incoming;
            header = true
        }
    }

}

void determinePitch(){
    // Determine string frequency
}

void configureADS() {
    // I2C Interface
}

void readADS() {
    // I2C Interface
}