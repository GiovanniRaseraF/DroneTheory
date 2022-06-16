// The library has the goal to implement a filter
// that allows to smooth the input
// Author: Giovanni Rasera - https://www.github.com/GiovanniRaseraF
#pragma once
#include "stdint.h"
#include "assert.h"
#include <Arduino.h>

#define MAX_CHANNELS 6

#define MIN_STICK 1000
#define MAX_STICK 2000

#define PWM_PULSE_MIN   750       // minimum PWM pulse width which is considered valid
#define PWM_PULSE_MAX   2250      // maximum PWM pulse width which is considered valid

class SPPM
{
public:
    // PPM Channels names
    enum ch {
        rightStick_LeftRight = 0,
        rightStick_UpDown,
        leftStick_UpDown,
        leftStick_LeftRight,
        VRA,
        VRB
    };

protected:
    // Stores all channel values
    uint32_t rawChValue[MAX_CHANNELS] = {0};
    int countCh = 0;

private:
    // Interrups
    int interruptPin = 3;   // 3 by default
    uint32_t prevInterruptMicros = 0;
    static SPPM *sppm; // necessary to have interrupts

    // Functions
public:
    SPPM(int pin);
    ~SPPM();

    uint32_t getValue(int channel);

private:
    static void SPPM_ISR();

    void changeState(uint32_t accurTimeMillis);
};
