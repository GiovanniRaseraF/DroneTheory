#include "SimplePPM.h"

// Radio
SPPM sppm = SPPM(3);

void setup()
{
    // Serial init
    Serial.begin(115200);
}

void loop()
{
    // Main task loop
    for (int i = 0; i < MAX_CHANNELS; i++) {
        Serial.print(sppm.getValue(i));
        Serial.print(" ");
    }
    Serial.println();

    delay(10);
}
