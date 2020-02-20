/*
 * NSM Cansat Bootcamp
 * LoRa Communication - Receiving
 * https://circuitdigest.com/microcontroller-projects/arduino-lora-sx1278-interfacing-tutorial
 * https://iotdesignpro.com/projects/lora-communication-between-two-arduino-using-LoRa-Module-SX1278
 * https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
 */

#include <LoRa.h>
#define lora_frequency 433E6

void setup() {
  
  Serial.begin(115200); 

  while (!Serial); 

  Serial.println("LoRa Communication - Receiving");

  if (!LoRa.begin(lora_frequency)) {
    Serial.println("LoRa Communication - Start Failed");
    while (1);
  }
  
}

void loop() {

  int packet_size = LoRa.parsePacket();
  
  if (packet_size) {
    Serial.print("Received packet '");
  
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

}
