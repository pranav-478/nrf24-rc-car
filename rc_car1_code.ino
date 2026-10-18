#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";
int receivedData[2]; 

// L298N Motor Control Pins
int IN1 = 2; // Left Motors
int IN2 = 3; 
int IN3 = 4; // Right Motors
int IN4 = 5; 

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    int x = receivedData[0]; // Left/Right
    int y = receivedData[1]; // Forward/Backward
    
    if (y > 600) { // Joystick Pushed UP -> Drive Forward
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
    } 
    else if (y < 400) { // Joystick Pulled DOWN -> Drive Reverse
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  
    } 
    else if (x > 600) { // INVERTED: Turn Right 
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
    } 
    else if (x < 400) { // INVERTED: Turn Left 
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  
    } 
    else { // Joystick Centered -> Stop
      digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    }
  }
}