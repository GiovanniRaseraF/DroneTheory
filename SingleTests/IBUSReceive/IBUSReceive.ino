void read_serial(void);
bool frame_validation(uint8_t *buffer);
void set_data(uint8_t *buffer);
uint16_t get_channel(uint8_t channel);
#define CHANNEL_SIZE 10
uint16_t data[CHANNEL_SIZE];

void setup() {
  Serial.begin(115200);
}

void loop() {
  read_serial();

}

void read_serial(void) {
  if (Serial.available() > 26) {
    if (Serial.read() == 0x20 ) { // Start bit of frame
      uint8_t buffer[26];
      buffer[0] = 0x20;


      uint8_t i;
      for (i = 1; i < 26; i++) {
        buffer[i] = Serial.read();
      }

      //      for (i = 0; i < 26; i++) {
      //      Serial.print(buffer[i], HEX);
      //    Serial.print(" ");
      // }

      Serial.println();

      //if (frame_validation(buffer) == true) {
      set_data(buffer);
      return;
      //}
    }
  } return;
}

bool frame_validation(uint8_t *buffer) {
  uint8_t i;
  uint16_t checksum = 0xFFFF;
  uint16_t rxChecksum = 0x0000;

  for (i = 0; i < 24; i++) {
    checksum -= buffer[i];
  }

  rxChecksum = buffer[25] + (buffer[26] << 8);

  if (rxChecksum == checksum) {
    return true;
  } else {
    return false;
  }
}

void set_data(uint8_t *buffer) {
  uint8_t i;

  for (i = 1; i < CHANNEL_SIZE + 1; i++) {
    data[i - 1] = buffer[i * 2] + (buffer[i * 2 + 1] << 8);
  }

  for (i = 1; i < CHANNEL_SIZE + 1; i++) {
    Serial.print(data[i - 1]);
    Serial.print(" ");
  }
  Serial.println();

}

uint16_t get_channel(uint8_t channel) {
  return data[channel];
}
