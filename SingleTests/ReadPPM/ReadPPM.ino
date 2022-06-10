#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 3;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);
byte motorPin = 7;

void setup() {
    Serial.begin(115200);
    pinMode(motorPin, OUTPUT);
}

void loop() {
    //analogWrite(motorPin, 1023); 
    // Print latest valid values from all channels
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(value);
        if (channel == 2)
          analogWrite(motorPin, map(value, 1600, 2000, 0, 1024)); 
        if(channel < channelAmount) Serial.print('\t');
    }
    Serial.println();
    delay(20);
}
