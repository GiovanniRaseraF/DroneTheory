#include "SimplePPM.h"
#include "assert.h"

SPPM *SPPM::sppm;

// Interrupts
static void SPPM::SPPM_ISR_FALLING(){
    assert(SPPM::sppm != NULL);
    
    uint32_t accurTime = micros();
    SPPM::sppm->changeState(accurTime, FALLING);
    SPPM::sppm->prevTimeFALLING = accurTime;
    attachInterrupt(digitalPinToInterrupt(SPPM::sppm->interruptPin), SPPM_ISR_RISING, RISING);
}

static void SPPM::SPPM_ISR_RISING(){
    assert(SPPM::sppm != NULL);
    
    uint32_t accurTime = micros();
    SPPM::sppm->changeState(accurTime, RISING);
    SPPM::sppm->prevTimeRISING = accurTime;
    attachInterrupt(digitalPinToInterrupt(SPPM::sppm->interruptPin), SPPM_ISR_FALLING, FALLING); 
}

SPPM::SPPM(){
    // Whait for first rising
    pinMode(interruptPin, INPUT_PULLUP);
    SPPM::sppm = this;
    attachInterrupt(digitalPinToInterrupt(this->interruptPin), SPPM_ISR_RISING, RISING);

    noInterrupts();
    this->currentState = NO_CONN;
    interrupts();
}

SPPM::~SPPM(){}

void SPPM::changeState(uint32_t accurTimeMillis, int direction){
    if(direction == RISING){
        if(this->currentState == NO_CONN){
            this->count = 0;
        }
        if(this->currentState == RECEIVING_CH_VALUE){
            this->rawValue = 0;
        } 
    }else{
        if(this->currentState == NO_CONN){
            this->rawValue = accurTimeMillis - this->prevTimeRISING;
            if(this->rawValue >= PWM_PULSE_MAX){
                this->currentState = RECEIVING_CH_VALUE;
            }
        }else if(this->currentState == RECEIVING_CH_VALUE && this->count < MAX_CHANNELS){
            this->rawValue = accurTimeMillis - this->prevTimeRISING;
            this->rawChValue[count] = rawValue;
            count++;
        }else{
            this->currentState = NO_CONN;
        }
    }
}
