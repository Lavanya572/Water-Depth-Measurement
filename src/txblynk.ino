//Incuding arduino default SPI library
#include <SPI.h>
//Incuding LoRa library
#include <LoRa.h>
#include <NewPing.h>
#include <ArduinoJson.h> //REQUIRES ARDUINO JSON V6
#include<String.h>

//define the pins used by the transceiver module
#define NSS 10
#define RST 9
#define DI0 2

#define TRIGGER_PIN 4  // Define the trigger pin (D1)
#define ECHO_PIN 3    // Define the echo pin (D2)

NewPing sonar(TRIGGER_PIN, ECHO_PIN);  // Create an instance of the NewPing library


void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  
  //attachInterrupt(BUTTON, ISR, FALLING);
  Serial.println("LoRa Sender");
  //setup LoRa sender
  LoRa.setPins(NSS, RST, DI0);
 
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF1) to match the receiver LoRa
  // This code ensure that you don't get LoRa messages
  // from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");
}

void loop() {
  //Serial.print("Sending packet: ");

  unsigned int distance = sonar.ping_cm();  // Send a ping and get the distance in centimeters
  Serial.println("Sending packets: ");

  LoRa.beginPacket();
  //LoRa.print(message);

  if (distance == 0) {
    LoRa.print("Out of range");  // Print a message if the sensor is out of range
  } else {
    LoRa.print("Water Depth: ");
    LoRa.print(distance);
    LoRa.print(" cm");  // Print the water depth in centimeters
  }

  if (distance == 0) {
    Serial.println("Out of range");  // Print a message if the sensor is out of range
  } else {
    Serial.println("Water Depth: ");
    Serial.print(distance);
    Serial.println(" cm");  // Print the water depth in centimeters
  }

  LoRa.endPacket();
  
  //Serial.println("Message sent: " + message);
  
   delay(500);
}