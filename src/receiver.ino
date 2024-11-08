#define BLYNK_TEMPLATE_ID "TMPL3JLG0IrHM"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "a7loU68cogNMZzv2SMupfLxDqTEDDY3Y"
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define NSS 4
#define RST 5
#define DI0 2

char ssid[] = "MilKyWay";
char pass[] = "MILKYWAY2002";

BlynkTimer timer;

String LoRaData;

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Blynk.virtualWrite(V0, value);
}

// void sendSensor() {
//   int packetSize = LoRa.parsePacket();
  
//   if (packetSize) {
//     Serial.print("Received packet: ");
    
//     while (LoRa.available()) {
//       LoRaData = LoRa.readString();
//       Serial.println("LoRa Data: " + LoRaData);

//       // Extract the numeric value from the LoRaData string
//       int receivedDistance = LoRaData.substring(15, LoRaData.indexOf(" cm")).toInt();
//       // Adjust substring indices based on the actual format
//       Serial.println("Received Distance: " + String(receivedDistance));

//       // Send the extracted data to Blynk with proper formatting
//       Blynk.virtualWrite(V0, "Water Depth: " + String(receivedDistance) + " cm");
//       // Send the extracted data to Blynk
//       // Blynk.virtualWrite(V0, receivedDistance);
//     }

//     Serial.println("End of packet.");
//   }
// }

// new void sensor data
void sendSensor() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.print("Received packet: ");

    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.println("LoRa Data: " + LoRaData);

      // Extract the numeric value from the LoRaData string
      int indexOfCm = LoRaData.indexOf(" cm");
      int receivedDistance = 0;

      if (indexOfCm != -1) {
        int startIdx = 13; // Adjust based on the actual format
        int endIdx = indexOfCm;
        String distanceStr = LoRaData.substring(startIdx, endIdx);
        receivedDistance = distanceStr.toInt();
        Serial.println("Received Distance: " + String(receivedDistance));
      } else {
        Serial.println("Error: 'cm' not found in LoRaData");
      }

      // Generate a unique timestamp for each update
      unsigned long currentMillis = millis();

      // Send the extracted data to Blynk with proper formatting
      Blynk.virtualWrite(V0, "Water Depth: " + String(receivedDistance) + " cm - " + String(currentMillis));
      delay(1000);  // Adjust the delay as needed
    }

    Serial.println("End of packet.");
  }
}




void setup() {
  Serial.begin(115200);
  Serial.println("LoRa Receiver");

  LoRa.setPins(NSS, RST, DI0);

  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
