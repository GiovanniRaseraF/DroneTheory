#include <string.h>

#define IBUS_BUFFSIZE 22    // Max iBus packet size (2 byte header, 14 channels x 2 bytes, 2 byte checksum)
#define IBUS_MAXCHANNELS 10 // My TX only has 10 channels, no point in polling the rest

int ledPin = 9;
bool forse = false;
bool cominciamo = false;
bool finitoLettura = false;
static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS] = {0};
uint16_t data[IBUS_MAXCHANNELS];
static boolean rxFrameDone;

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
    if(i == 1 or i == 7){
    Serial.print("Ch");
    Serial.print(i);
    Serial.print(" ");}
  }
  Serial.println();
}

void loop()
{
  readRx();
  
  //delay(3);
}

void readRx()
{
  if (Serial.available())
  {
    uint8_t val = Serial.read();
    if (val == 32) {
      forse = true;
      return;
    }
    
    if (forse && val == 64) {
      cominciamo = true;
      return;
    }

    if (cominciamo) {
      ibus[ibusIndex] = val;
      ibusIndex++;
      
      if (ibusIndex == IBUS_BUFFSIZE)
        finitoLettura = true;

      
      
      if (finitoLettura) {
        //erial.println(ibus[10]);
        // Salvo
        int high = 1;
        int low = 0;
      
        for (int i = 0; i < IBUS_MAXCHANNELS; i++) {
          rcValue[i] = (ibus[high] << 8) + ibus[low];
          if(i == 1 or i == 7){
          Serial.print(rcValue[i]);
          Serial.print(" ");}
          high += 2;
          low += 2;
        }
        Serial.println();

        forse = false;
        cominciamo = false;
        finitoLettura = false;
        ibusIndex = 0;
      }
    }
  }
}
