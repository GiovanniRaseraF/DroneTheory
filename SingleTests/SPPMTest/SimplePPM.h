// The library has the goal to implement a filter 
// that allows to smooth the input 
// Author: Giovanni Rasera - https://www.github.com/GiovanniRaseraF
#pragma once
#include "stdint.h"
#include <Arduino.h>

#define MAX_CHANNELS 6

#define MIN_STICK 1000
#define MAX_STICK 2000

#define PWM_PULSE_MIN   750       // minimum PWM pulse width which is considered valid
#define PWM_PULSE_MAX   2250      // maximum PWM pulse width which is considered valid

class SPPM{
    public:
    // PPM Channels names
    enum ch{
        rightStick_LeftRight = 0,
        rightStick_UpDown       ,
        leftStick_UpDown        ,
        leftStick_LeftRight     ,
        VRA                     ,
        VRB                 
    };

    enum state{
        NO_CONN              = 0,
        READY_FOR_HEADER        ,
        RECEIVING_HEADER        ,
        READY_FOR_CH_VALUE      ,
        RECEIVING_CH_VALUE
    };
    int currentState = NO_CONN;

    // protected:
    // Stores all channel values
    int rawChValue[MAX_CHANNELS] = {0};

    // private:
    // Interrups
    int interruptPin = 3;   // 3 by default
    uint32_t prevTimeRISING = 0;
    uint32_t prevTimeFALLING = 0;

    static SPPM *sppm; // necessary to have interrupts

    int count = 0;
    uint32_t rawValue = 0;

    // Functions
    SPPM();
    ~SPPM();

    static void SPPM_ISR_RISING();
    static void SPPM_ISR_FALLING();

    void changeState(uint32_t accurTimeMillis, int direction);
};
