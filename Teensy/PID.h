//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/5/20.
//

#ifndef CHAMELEON_PID_H
#define CHAMELEON_PID_H

#define STEADY_STATE_DEV 10
#define FREQ_DEV 5

#include "Config.h"
#include "Pickup.h"
#include <Arduino.h>

class PIDMotor {
private:
    double kp = 0;
    double ki = 0;
    double kd = 0;
    double kp_f = 0;
    double ki_f = 0;
    double kd_f = 0;
    int pwm = 0;
    int enc = 0;
    int dir = 0;
    int target_f = 0;
    int target_deg = 0;
    volatile double deg_delta = 0;
    double last_freq = 0;
    double cumError = 0;
    double prev_error = 0;
    double prev_timestamp = 0;
    double errorRate = 0;

    void setEffort(int effort);
    void encoderISR();

public:
    PIDMotor(int string);
    void setPID(double p, double i, double d, bool freq);
    void process(ADS pickup);
    void setTarget(int frequency);
    void setSetpoint(double degrees);
    bool targetReached();
};

#endif //CHAMELEON_PID_H
