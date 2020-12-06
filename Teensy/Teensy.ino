//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/3/20.
//

#include "Config.h"
#include <Wire.h>

int note = -1;
bool header = true;
unsigned int notes[7];

void setup() {
    Serial.begin(115200);
    HW_SERIAL.begin(9600);
    Wire.begin();

    pinMode(STRING1_PWM, OUTPUT);
    pinMode(STRING1_DIR, OUTPUT);
    configureADS();
}

void loop() {
    // UART from Arduino - Send string number then frequency
    if (HW_SERIAL.available() > 0) {
        int incoming = HW_SERIAL.read();
        if (header) {
            note = incoming - 1;
            header = false;
        } else {
            notes[note] = incoming;
            header = true;
        }
    }

}

void determinePitch(){
    // Determine string frequency
}

void configureADS() {
    // I2C Interface
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01); // Register Address
    Wire.write(0x85); // MSB
    Wire.write(0xE3); // LSB
    Wire.endTransmission();
}

bool checkADSConfig() {
    // I2C Interface - check config
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01); // Register Address
    Wire.requestFrom(I2C_ADDR, 2);
    byte msb = Wire.read();
    byte lsb = Wire.read();
    Wire.endTransmission();

    uint16_t config = ((msb << 8) | lsb);
    uint16_t expected_data_rate = 0xE0;
    return ((config & expected_data_rate) == expected_data_rate);
}
