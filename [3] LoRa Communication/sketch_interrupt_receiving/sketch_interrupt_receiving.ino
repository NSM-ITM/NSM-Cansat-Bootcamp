/*
 * NSM Cansat Bootcamp
 * LoRa Communication - Receiving
 * https://circuitdigest.com/microcontroller-projects/arduino-lora-sx1278-interfacing-tutorial
 * https://iotdesignpro.com/projects/lora-communication-between-two-arduino-using-LoRa-Module-SX1278
 * https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
 */

#include <LoRa.h>
#define lora_frequency 433E6
#define interrupt_pin 2 // LoRa's DIO0

void setup() {
  
  Serial.begin(115200); 

  while (!Serial); 

  Serial.println("LoRa Communication - Receiving");

  if (!LoRa.begin(lora_frequency)) {
    Serial.println("LoRa Communication - Start Failed");
    while (1);
  }

  LoRa.onReceive(receive_transaction);
  LoRa.receive();
  
}

void loop() {

  
}

void receive_transaction(int packet_size) {
  Serial.println("LoRa Communication - Incoming Transaction Interrupt");

  
  if (packet_size) {
    String received_transaction = "";
    
    Serial.print("Received packet '");
    while (LoRa.available()) {
      char new_char = (char) LoRa.read();
      received_transaction += new_char;
    }

    Serial.print(received_transaction);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    
  }
}
