#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 3;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

// PPM Channels
const byte leftStick_UpDown = 3;
const byte rightStick_UpDown = 2;
const byte leftStick_LeftRight = 4;
const byte rightStick_LeftRight = 1;
const byte VRA = 5;
const byte VRB = 6;

void setup() {
  Serial.begin(115200);

  for (byte channel = 1; channel <= channelAmount; ++channel) {
    Serial.print("Ch");
    Serial.print(channel);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  for (byte channel = 1; channel <= channelAmount; ++channel) {
    unsigned value = ppm.latestValidChannelValue(channel, 0);


    int power = map(value, 1000, 2000, 0, 200);

    Serial.print(value);
    Serial.print(" ");

  }

  Serial.println();

  delay(20);
}
