# Jeep Radiocomandata
## Componenti
- Arduino Nano, ATmega328P (Old Bootloader)
- L298N Modulo, ESC per motori CC
- Radio FlySky
- Ricevente FlySky FS-A8S
- Motori 10V CC
- Cavo usb mini per il flashing
- Tester
- Batteria 4S a 14V

## Software 
- Arduino IDE o equivalenti

## Schematica
- file: [Schematica](./Schematica.jpeg)

## Canali
```c
// PPM Channels
const byte rightStick_LeftRight = 1;
const byte rightStick_UpDown    = 2;
const byte leftStick_UpDown     = 3;
const byte leftStick_LeftRight  = 4;
const byte VRA                  = 5;
const byte VRB                  = 6;
```
