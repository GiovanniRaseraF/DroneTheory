#include <PPMReader.h>

#define AVANTI 3

// Radio
const byte interruptPin     = 3;
const byte channelAmount    = 6;
byte chValue[channelAmount] = {0};
PPMReader ppm(interruptPin, channelAmount);

// Pin Motori
byte backPower_pin    = 5;
byte backDir1_pin     = 6;
byte backDir2_pin     = 7;

byte frontPower_pin   = 8;
byte frontDir1_pin    = 8;
byte frontDir2_pin    = 10;

// Func
void printHeaderChannels();
void readRadio();

void setup() {
  // Serial init
  Serial.begin(115200);
  //printHeaderChannels();

  // Motors
  pinMode(backPower_pin,      OUTPUT);
  pinMode(backDir1_pin,       OUTPUT);
  pinMode(backDir2_pin,       OUTPUT);

  pinMode(frontPower_pin,     OUTPUT);
  pinMode(frontDir1_pin,      OUTPUT);
  pinMode(frontDir2_pin,      OUTPUT);
}

void loop() {
  digitalWrite(backDir1_pin, HIGH);
  digitalWrite(backDir2_pin, LOW);

  readRadio();
  delay(10);
}

void readRadio(){
  // Read
  for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);

        chValue[channel - 1] = value;
  }

  // Display
  for (byte channel = 1; channel <= channelAmount; ++channel) {
      unsigned value = chValue[channel - 1];
      
      if(channel == AVANTI){
        int power = map(value, 1000, 2000, 0, 50);
        analogWrite(backPower_pin, power); 

        //Serial.print(power);
        //Serial.print(" ");
      }

      if(channel == 2){
        int power = map(value, 1000, 2000, 0, 50);
        Serial.print(power);
        /*
        if(value < 1300 && value >= 1000){
          // Destra 
          digitalWrite(frontDir1_pin, LOW);
          digitalWrite(frontDir2_pin, HIGH);
          
          int powerTork = 30 - map(value, 1000, 1300, 0, 30);
          analogWrite(frontPower_pin, powerTork);

          Serial.print(powerTork);
        }else if (value > 1700 && value <= 2000){
          // Sinistra
          digitalWrite(frontDir1_pin, HIGH);
          digitalWrite(frontDir2_pin, LOW);
          
          int powerTork = map(value, 1700, 2000, 0, 30);
          analogWrite(frontPower_pin, powerTork);
          
          Serial.print(powerTork);
        }else{
          Serial.print(0);
        }
        */
      }      
  }
  Serial.println();
}

// Func Implementation
void printHeaderChannels(){
  //while(!Serial){}
  
  for (byte channel = 1; channel <= channelAmount; ++channel) {
    Serial.print(channel);
    Serial.print(" ");
  }
  
  Serial.println();
}
