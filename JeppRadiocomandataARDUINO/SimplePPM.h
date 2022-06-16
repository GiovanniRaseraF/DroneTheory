// The library has the goal to implement a filter 
// that allows to smooth the input 
// Author: Giovanni Rasera - https://www.github.com/GiovanniRaseraF
#pragma once

#define MAX_CHANNELS 6

#define MIN_STICK 1000
#define MAX_STICK 2000

#define PWM_PULSE_MIN   750       // minimum PWM pulse width which is considered valid
#define PWM_PULSE_MAX   2250      // maximum PWM pulse width which is considered valid

class SimplePPM{
    public:
    // PPM Channels names
    const byte rightStick_LeftRight = 1;
    const byte rightStick_UpDown    = 2;
    const byte leftStick_UpDown     = 3;
    const byte leftStick_LeftRight  = 4;
    const byte VRA                  = 5;
    const byte VRB                  = 6;
    
    protected:
    // Stores all channel values
    int rawChValue[MAX_CHANNELS] = {0};

    private:
    // Interrups
    int interruptPin = 3;   // 3 by default


};