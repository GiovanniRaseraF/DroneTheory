#include "SimplePPM.h"

SPPM *SPPM::sppm;

// Interrupts
void SPPM::SPPM_ISR(){
    assert(SPPM::sppm != NULL);
    
    uint32_t accurTime = micros();
    SPPM::sppm->changeState(accurTime);
    SPPM::sppm->prevInterruptMicros = accurTime;
}

SPPM::SPPM(int pin){
    this->interruptPin = pin;
    SPPM::sppm = this;
    
    pinMode(this->interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(this->interruptPin), SPPM_ISR, RISING);
}

SPPM::~SPPM(){
    detachInterrupt(digitalPinToInterrupt(this->interruptPin));
}

void SPPM::changeState(uint32_t accurTimeMicros){
    uint32_t deltaTime = accurTimeMicros - this->prevInterruptMicros;

    if(deltaTime >= PWM_PULSE_MAX){
        // Packet started
        this->countCh = 0;
    }else if(deltaTime > PWM_PULSE_MIN && deltaTime < PWM_PULSE_MAX && countCh < MAX_CHANNELS){
        this->rawChValue[this->countCh] = constrain(deltaTime, MIN_STICK, MAX_STICK);
        this->countCh++;
    }
}

uint32_t SPPM::getValue(int channel){
    assert(channel >= 0 && channel < MAX_CHANNELS);
    channel = constrain(channel, 0, MAX_CHANNELS);

    noInterrupts();
    uint32_t ret = this->rawChValue[channel];
    interrupts();

    return ret;
}
