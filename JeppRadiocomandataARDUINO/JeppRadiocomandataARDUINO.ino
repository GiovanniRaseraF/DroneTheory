#include <PPMReader.h>
#include "SimplePPM.h"

#define RIGHT     1
#define LEFT      2
#define FARWARD   1
#define BACKWARD  2
#define MIN_STICK 1000
#define MAX_STICK 2000

#define MAX_BACK_MOTOR_POWER  200
#define MAX_FRONT_MOTOR_POWER 150

// Radio
const byte interruptPin     = 3;
const byte channelAmount    = 6;
int chValue[channelAmount]  = {0};
PPMReader ppm(interruptPin, channelAmount);

// PPM Channels
const byte rightStick_LeftRight = 1;
const byte rightStick_UpDown    = 2;
const byte leftStick_UpDown     = 3;
const byte leftStick_LeftRight  = 4;
const byte VRA                  = 5;
const byte VRB                  = 6;

// Pin Motors
byte backPower_pin    = 5;
byte backDir1_pin     = 6;
byte backDir2_pin     = 7;

byte frontPower_pin   = 10;
byte frontDir1_pin    = 9;
byte frontDir2_pin    = 8;

// Func
void printHeaderChannels();
void readRadio();
void displayRadio();
void writeToMotor();

void setup()
{
    // Serial init
    Serial.begin(115200);
    printHeaderChannels();

    // Motors
    pinMode(backPower_pin,      OUTPUT);
    pinMode(backDir1_pin,       OUTPUT);
    pinMode(backDir2_pin,       OUTPUT);

    pinMode(frontPower_pin,     OUTPUT);
    pinMode(frontDir1_pin,      OUTPUT);
    pinMode(frontDir2_pin,      OUTPUT);
}

void loop()
{
    // Main task loop
    readRadio();
    displayRadio();
    writeToMotor();

    delay(10);
}

// 1000 -*- 2000
void writeToMotor()
{
    const int minToLeft = 1300;
    const int minToRight = 1700;

    // Settig direction and power for motors
    int powerFarward = chValue[leftStick_UpDown - 1];
    int power = map(powerFarward, MIN_STICK, MAX_STICK, 0, MAX_BACK_MOTOR_POWER);
    int directionValue = chValue[rightStick_LeftRight - 1];

    int direction = (directionValue < minToLeft ? LEFT : 0);
    direction     = (directionValue > minToRight ? RIGHT : direction);
    int directionPower = 0;

    switch (direction) {
        case LEFT:
            directionPower = MAX_FRONT_MOTOR_POWER - map(directionValue, MIN_STICK, minToLeft, 0, MAX_FRONT_MOTOR_POWER);

            digitalWrite(frontDir1_pin, HIGH);
            digitalWrite(frontDir2_pin, LOW);

            analogWrite(frontPower_pin, directionPower);
            break;
        case RIGHT:
            directionPower = map(directionValue, minToRight, MAX_STICK, 0, MAX_FRONT_MOTOR_POWER);

            digitalWrite(frontDir1_pin, LOW);
            digitalWrite(frontDir2_pin, HIGH);

            analogWrite(frontPower_pin, directionPower);
            break;
        default:
            directionPower = 0;

            digitalWrite(frontDir1_pin, LOW);
            digitalWrite(frontDir2_pin, LOW);

            analogWrite(frontPower_pin, directionPower);
            break;
    }

    // Farward or Backward
    int nobAValue = chValue[VRA - 1];
    int move = (nobAValue < 1500 ? BACKWARD : FARWARD);

    switch(move){
      case FARWARD:
        digitalWrite(backDir1_pin, HIGH);
        digitalWrite(backDir2_pin, LOW);
        break;
      case BACKWARD:
        digitalWrite(backDir1_pin, LOW);
        digitalWrite(backDir2_pin, HIGH);
        break;
     default:
        break;
    }
    analogWrite(backPower_pin, power);
}

void displayRadio()
{
    // Display
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = chValue[channel - 1];
        Serial.print(value);
        Serial.print(" ");
    }
    Serial.println();
}

void readRadio()
{
    // Read
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        unsigned value = ppm.latestValidChannelValue(channel, 0);

        chValue[channel - 1] = value;
    }
}

// Func Implementation
void printHeaderChannels()
{
    //while(!Serial){}
    Serial.println("rightStick_LeftRight rightStick_UpDown leftStick_UpDown leftStick_LeftRight VRA VRB ");
}
