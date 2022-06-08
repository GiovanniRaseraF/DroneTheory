#include <string.h>

#define IBUS_BUFFSIZE 32    // Max iBus packet size (2 byte header, 14 channels x 2 bytes, 2 byte checksum)
#define IBUS_MAXCHANNELS 10 // My TX only has 10 channels, no point in polling the rest

int ledPin = 9;
bool forse = false;
bool cominciamo = false;
bool finitoLettura = false;
static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS]={0};

static boolean rxFrameDone;

void setup()
{
  Serial.begin(115200);
  Serial.println("Ciao Giovanni");
}

void loop()
{
  readRx();
  //delay(100);
}

void readRx()
{
  rxFrameDone = false;

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
        // Salvo
        int high=1;
        int low=0;
        for(int i = 6; i < IBUS_BUFFSIZE; i++){
          Serial.print(ibus[i]);
          Serial.print(" ");
        }

        Serial.println();
        
        for (int i = 0; i < IBUS_MAXCHANNELS && false; i++) {
          //left shift away the first 8 bits of the first byte and add the whole value of the previous one
          rcValue[i] = ((ibus[high] << 8) & (0x0FFF)) + ibus[low];
          
          high += 2;
          low += 2;
          
          
          if(i == 1 && false){
          Serial.print("Ch");
          Serial.print(i+1);
          Serial.print(" ");
          Serial.println(rcValue[i]);}
        }

        forse = false;
        cominciamo = false;
        finitoLettura = false;
        ibusIndex = 0;
      }
    }
}}
