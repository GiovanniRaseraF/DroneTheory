#include "BLEDevice.h"
#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include <vector>
#include <time.h>

// Threads
void TaskCalculatePrime(void *pvParam);
void TaskCalculatePrime(void *pvParam){
  std::vector<int> primes{2};
  int a = 1;
  
  while(true){
    bool isp = true;
    for(int p : primes){
      if(a % p == 0){
        isp = false;
      }
    }

    if(isp){
      primes.push_back(a);
    }

    if((a-1) % 4000000 == 0){
      Serial.print(a);
      Serial.println(" 4000000 operazioni fatte");
    } 
    a += 2;   
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){};
  TaskCalculatePrime(nullptr);
}

void loop() {
  // put your main code here, to run repeatedly:
}
