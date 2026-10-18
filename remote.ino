#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";

const int joyX = A0;
const int joyY = A1;
int joyData[2]; // Array to hold [X, Y]

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  joyData[0] = analogRead(joyX); // Read X-axis (0-1023)
  joyData[1] = analogRead(joyY); // Read Y-axis (0-1023)

  radio.write(&joyData, sizeof(joyData));
  delay(50); // Small delay for stability
}