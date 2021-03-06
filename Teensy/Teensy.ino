//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/3/20.
//

#include "Config.h"
#include "PID.h"
#include "Pickup.h"
#include <Wire.h>

int note = -1;
int content = 0;
bool tune = false;
unsigned int notes[7];
PIDMotor motor1;
ADS pickup_ic;
// For counting ticks
volatile double motor1_count = 0;

void setup() {
    Serial.begin(9600);
    HW_SERIAL.begin(9600);
    Wire.begin();
    attachInterrupt(STRING1_ENC, encoderISR1, RISING);

    pickup_ic = ADS(); // Configures IC if necessary
    motor1 = PIDMotor(1);
    // TODO: Set PID
}

void loop() {
    // UART from Arduino - Send operation command, then string number, then frequency
    // Use this to determine if we start tuning or go direct to note
    if (HW_SERIAL.available() > 0) {
        int incoming = HW_SERIAL.read();
        if (content == 0) {
            tune = false;
            if (incoming == "TUNE") {
                tune = true;
            }
        } else if (content == 1) {
            note = incoming - 1;
            content++;
        } else {
            notes[note] = incoming;
            content = 0;
        }
    }

    // Test and tune motor PID
    motor1.setSetpoint(360);
    motor1.process(pickup_ic); // Execute PID loop
    delay(10);
    Serial.print(motor1_count);
    Serial.print('\n');
    if (motor1_count > 200) { // Assumes 200 ticks per revolution
      Serial.print("done");
      Serial.print("\nDegrees: ");
      Serial.print(motor1_count * 1.8);
      motor1.setEffort(0); // Stop motor
      delay(10000);
    }

    // If pickup is in listening state, sample the frequency
    if (pickup_ic.isListening()) {
        pickup_ic.sample();
    }

    // When running PID
    if (!motor1.targetReached()) {
        motor1.process(pickup_ic);
    } else {
        pickup_ic.stopListening();
        HW_SERIAL.write("TUNE COMPLETE");
    }

    // To test that motor go brr
    //motor1.setEffort(100);
    //delay(200);
}

void startTuning(PIDMotor motor, int frequency) {
    motor.setTarget(frequency);
    pickup_ic.startListening();
}

void encoderISR1() {
    motor1_count++;
}
