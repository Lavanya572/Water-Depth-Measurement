# Water-Depth-Measurement

A UAV system for water depth measurement using ultrasonic sensors and LoRa communication.

## Features
- Real-time data transmission to ground station via LoRa
- Data analysis and visualization using Blynk IoT cloud

## Getting Started
### Prerequisites
#### Hardware:
- UAV (drone)
- ESP32
- Arduino Microcontroller
- Waterproof ultrasonic sensor
- LoRa communication modules

#### Software:
- Arduino IDE (for programming the UAV controller)
- Blynk IoT account for cloud data visualization

### Hardware Assembly:

Attach the ultrasonic sensor to the UAV and connect it to the flight controller.
Connect the LoRa module to the UAV for long-range data transmission.

### Software Setup:

Install the required libraries for LoRa and Blynk in the Arduino IDE.
Flash the provided code (src/) to the UAV's microcontroller (e.g., ESP32 or Arduino).
##### Blynk Integration:
Create a new project in the Blynk app and configure widgets for real-time data display.
Update the Blynk credentials in the code to link it to your Blynk project.


### Technologies Used
- Ultrasonic Sensor: Measuring water depth.
- LoRa Communication: Long-range, low-power data transmission.
- Protocols: IEEE 802.11 b/g/n 
- Blynk IoT Platform: Cloud-based data storage and visualization.
- Arduino IDE: Code development for UAV control and sensor data processing.
