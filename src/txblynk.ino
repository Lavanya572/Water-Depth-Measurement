//Incuding arduino default SPI library
#include <SPI.h>
//Incuding LoRa library
#include <LoRa.h>
#include <NewPing.h>
#include<String.h>

//define the pins used by the transceiver module
#define NSS 11
#define RST 8
#define DI4 7

#define TRIGGER_PIN 4  // Define the trigger pin (D1)
#define ECHO_PIN 3    // Define the echo pin (D2)

NewPing sonar(TRIGGER_PIN, ECHO_PIN);  // Create an instance of the NewPing library


void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  
  //attachInterrupt(BUTTON, ISR, FALLING);
  Serial.println("LoRa Sender");
  //setup LoRa sender
  LoRa.setPins(NSS, RST, DI4);
 
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("LoRa Initializing Successful!");
}

void loop() {
  Serial.print("Sending packet: ");
  int distance = sonar.ping_cm();  // Send a ping and get the distance in centimeters

  LoRa.beginPacket();
  //LoRa.print(message);

  if (distance == 0) {
    LoRa.print("Out of range");  // Print a message if the sensor is out of range
  } else {
    LoRa.print("Water Depth: ");
    LoRa.print(distance);
    LoRa.print(" cm");  // Print the water depth in centimeters
  }
  
  Serial.println("Message sent: " + message);
  
   delay(500);
}
