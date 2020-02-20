/*
 * NSM Cansat Bootcamp
 * LoRa Communication - Sending
 * https://circuitdigest.com/microcontroller-projects/arduino-lora-sx1278-interfacing-tutorial
 * https://iotdesignpro.com/projects/lora-communication-between-two-arduino-using-LoRa-Module-SX1278
 * https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
 */

#include <LoRa.h>
#define lora_frequency 433E6;

unsigned long start_time_counter;

void setup() {
  
  Serial.begin(115200);
  
  while (!Serial); 

  Serial.println("LoRa Communication - Sending");

  if (!LoRa.begin(lora_frequency)) {
    Serial.println("LoRa Communication - Start Failed");
    while (1);
  }
  
}

void loop() {

  start_time_counter = millis();
  
  LoRa.beginPacket();
  LoRa.print("Recent Broadcasting Time: ");
  LoRa.print(start_time_counter);
  LoRa.endPacket();

  Serial.print("Recent Broadcasting Time: ");
  Serial.println(start_time_counter);

  delay(5000);

}
