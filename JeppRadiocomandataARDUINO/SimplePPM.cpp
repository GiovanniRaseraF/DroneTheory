#include "SimplePPM.h"
#include "assert.h"

// Interrupts
static void SPPM_ISR_FALLING(){
    assert(SPPM::sppm != NULL);
    
    uint32_t accurTime = millis();
    SPPM::sppm->changeState(accurTime, FALLING);
    SPPM::sppm->prevTimeFALLING = accurTime;
    attachInterrupt(digitalPinToInterrupt(SPPM::sppm->interruptPin), SPPM_ISR_RISING, RISING);
}

static void SPPM_ISR_RISING(){
    assert(SPPM::sppm != NULL);
    
    uint32_t accurTime = millis();
    SPPM::sppm->changeState(accurTime, RISING);
    SPPM::sppm->prevTimeRISING = accurTime;
    attachInterrupt(digitalPinToInterrupt(SPPM::sppm->interruptPin), SPPM_ISR_FALLING, FALLING); 
}

SPPM::SPPM(){
    // Whait for first rising
    SPPM::sppm = this;
    attachInterrupt(digitalPinToInterrupt(this->interruptPin), SPPM_ISR_RISING, RISING);

    noInterrupts();
    this->currentState = NO_CONN;
    interrupts();
}

void SPPM::changeState(uint32_t accurTimeMillis, int direction){
    if(direction == FALLING){
        this->rawValue = accurTimeMillis - this->prevTimeRISING;
    }
}