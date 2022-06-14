#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 3;
byte channelAmount = 6;

int motorBackPinPower = 5, motorBackPin1 = 6, motorBackPin2 = 7;
PPMReader ppm(interruptPin, channelAmount);
byte motorPin = 7;

void setup() {
    Serial.begin(115200);
    
    pinMode(motorBackPinPower, OUTPUT);
    pinMode(motorBackPin1, OUTPUT);
    pinMode(motorBackPin2, OUTPUT);

    digitalWrite(motorBackPinPower, LOW);
    
}

void loop() {
    digitalWrite(motorBackPin1, HIGH);
    digitalWrite(motorBackPin2, LOW);
    
    
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);
        
        if(channel == 3){
          int power = map(value, 1000, 2000, 0, 200);
          analogWrite(motorBackPinPower, power); 

          Serial.print(value); 
          Serial.print(" ");
          Serial.print(power);
        }
    }
    
    Serial.println();
    
    delay(20);
}
