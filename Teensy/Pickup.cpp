//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/6/20.
//

#include "Pickup.h"

ADS::ADS() {
    if (!checkADSConfig()) {
        configureADS();
    }
}

void ADS::configureADS() {
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01); // Register Address
    Wire.write(0x85); // MSB
    Wire.write(0xE3); // LSB
    Wire.endTransmission();
}

bool ADS::checkADSConfig() {
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

double ADS::sample() {
    // Read and determine the actual frequency then save to variable (interrupts maybe)
}

void ADS::startListening() {
    listening = true;
}

void ADS::stopListening() {
    listening = false;
}

bool ADS::isListening() {
    return listening;
}

double ADS::getLastSample() {
    return current_freq;
}
