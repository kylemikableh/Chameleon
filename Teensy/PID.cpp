//
// Chameleon - Electromechanical String Instrument
// Created by Tom Nurse on 12/5/20.
//

#include "PID.h"

PIDMotor::PIDMotor(){}

PIDMotor::PIDMotor(int string) {
    switch (string){
        case 1:
            pwm = STRING1_PWM;
            dir = STRING1_DIR;
            enc = STRING1_ENC;
            pinMode(STRING1_PWM, OUTPUT);
            pinMode(STRING1_DIR, OUTPUT);
            break;

        case 2:
            pwm = STRING2_PWM;
            dir = STRING2_DIR;
            enc = STRING2_ENC;
            pinMode(STRING2_PWM, OUTPUT);
            pinMode(STRING2_DIR, OUTPUT);
            break;

        case 3:
            pwm = STRING3_PWM;
            dir = STRING3_DIR;
            enc = STRING3_ENC;
            pinMode(STRING3_PWM, OUTPUT);
            pinMode(STRING3_DIR, OUTPUT);
            break;

        case 4:
            pwm = STRING4_PWM;
            dir = STRING4_DIR;
            enc = STRING4_ENC;
            pinMode(STRING4_PWM, OUTPUT);
            pinMode(STRING4_DIR, OUTPUT);
            break;

        case 5:
            pwm = STRING5_PWM;
            dir = STRING5_DIR;
            enc = STRING5_ENC;
            pinMode(STRING5_PWM, OUTPUT);
            pinMode(STRING5_DIR, OUTPUT);
            break;

        case 6:
            pwm = STRING6_PWM;
            dir = STRING6_DIR;
            enc = STRING6_ENC;
            pinMode(STRING6_PWM, OUTPUT);
            pinMode(STRING6_DIR, OUTPUT);
            break;

        default:
            // Do nothing
            break;
    }
}

void PIDMotor::setPID(double p, double i, double d, bool freq) {
    if (freq) {
        kp_f = p;
        ki_f = i;
        kd_f = d;
    } else {
        kp = p;
        ki = i;
        kd = d;
    }
}

void PIDMotor::setTarget(int frequency) {
    target_f = frequency;
}

void PIDMotor::setSetpoint(double degrees) {
    deg_delta = 0;
    target_deg = degrees;
}

bool PIDMotor::targetReached() {
    bool reached = false;
    if (abs(target_deg - deg_delta) < STEADY_STATE_DEV){
        setEffort(0);
        target_deg = 0;
        deg_delta = 0;
        cumError = 0;
        prev_timestamp = 0;
        reached = true;
    } else if (abs(target_f - last_freq) < FREQ_DEV) {
        setEffort(0);
        target_f = 0;
        last_freq = 0;
        cumError = 0;
        prev_timestamp = 0;
        reached = true;
    }
    return reached;
}

void PIDMotor::setEffort(double effort) {
    if (effort > 0) {
        digitalWrite(STRING1_DIR, HIGH);
    } else {
        digitalWrite(STRING1_DIR, LOW);
    }

    if (effort > 255) {
        effort = 255;
    } else if (effort < -255) {
        effort = -255;
    }

    effort = 255 - abs(effort);
    analogWrite(STRING1_PWM, effort);
}

void PIDMotor::process(ADS pickup) {
    unsigned long timestamp = millis();
    unsigned long elapsed_time = timestamp - prev_timestamp;

    double p, i, d;
    double error;

    if (target_f > 0) {
        p = kp_f;
        i = ki_f;
        d = kd_f;
        int freq = pickup.getLastSample();
        last_freq = freq;
        error = target_f - freq;
    } else {
        p = kp;
        i = ki;
        d = kd;
        error = target_deg - deg_delta;
        //Serial.print(error);
    }

    if (prev_timestamp != 0) {
        cumError += error * elapsed_time;
        errorRate = (error - prev_error)/elapsed_time;
    }
    prev_timestamp = timestamp;
    prev_error = error;

    double effort = p * error + i * cumError + d * errorRate;
    setEffort(effort);
}
