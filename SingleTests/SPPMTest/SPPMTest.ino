#include "SimplePPM.h"

// Radio
SPPM sppm = SPPM();

void setup()
{
    // Serial init
    Serial.begin(115200);
    
}

void loop()
{
    // Main task loop
    Serial.println(sppm.rawValue);   
    delay(10); 
}
