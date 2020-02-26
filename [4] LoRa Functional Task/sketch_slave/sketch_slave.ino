/* 
 * NSM Cansat Bootcamp
 * LoRa Communication - Functional Task - Slave
 * https://circuitdigest.com/microcontroller-projects/arduino-lora-sx1278-interfacing-tutorial
 * https://iotdesignpro.com/projects/lora-communication-between-two-arduino-using-LoRa-Module-SX1278
 * https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
 */

#include <LoRa.h>
#define lora_frequency 433E6
#define lora_pair_id "NSM_1"
#define interrupt_pin 2 // LoRa's DIO0

int communication_state = 2;  // 1-sending, 2-receiving
long current_result = 1;
int remaining_value = 0;

void setup() {

  Serial.begin(115200);

  while (!Serial);

  Serial.println("LoRa Communication - Slave");

  if (!LoRa.begin(lora_frequency)) {
    Serial.println("LoRa Communication - Start Failed");
    while (1);
  }
  
  LoRa.onReceive(translate_received_transaction);
  
}

// sending format
// lora_pair_id|remaining_value|result
void loop() {

  // keep sending until proper response is received
  if(communication_state == 1) {
    
    LoRa.beginPacket();
    LoRa.print(lora_pair_id);
    LoRa.print("|");
    LoRa.print(current_result);
    LoRa.print("|");
    LoRa.print(remaining_value);
    LoRa.endPacket();  

    Serial.println("LoRa Communication - Sending Transaction");
    Serial.print(lora_pair_id);
    Serial.print("|");
    Serial.print(current_result);
    Serial.print("|");
    Serial.println(remaining_value);

    delay(5000);
    
  } 
  
}

void translate_received_transaction(int packet_size) {
  Serial.println("LoRa Communication - Incoming Transaction Interrupt");

  communication_state = 2;

  if (packet_size) {
    String received_transaction = "";
    
    Serial.print("Received packet '");
    while (LoRa.available()) {
      char new_char = (char) LoRa.read();
      received_transaction += new_char;
    }

    Serial.println(received_transaction);
    
    String received_pair_id        = get_field_by_position(received_transaction, (char) '|', 0);
    String received_current_result = get_field_by_position(received_transaction, (char) '|', 1);
    String received_remaining_value = get_field_by_position(received_transaction, (char) '|', 2);

    if(
      received_pair_id == lora_pair_id &&
      received_pair_id != "" &
      received_current_result != "" &
      received_remaining_value != ""
    ) {
      
      current_result = factorial_function(received_current_result.toInt(), received_remaining_value.toInt());

      if(received_remaining_value.toInt() > 0)
        remaining_value = received_remaining_value.toInt() - 1;
      
      communication_state = 1;
      
    }
    
  }
}


long factorial_function(long result, int remaining) {

  if(remaining == 0) {
    return result;
    
  } else {
    return result * remaining;
    
  }

}


String get_field_by_position(String data, char separator, int index) {
  int found = 0;
  int str_index[] = {0, -1};
  int max_index = data.length()-1;

  for(int i=0; i<=max_index && found<=index; i++){
    if(data.charAt(i)==separator || i==max_index){
        found++;
        str_index[0] = str_index[1]+1;
        str_index[1] = (i == max_index) ? i+1 : i;
    }
  }

  return found > index ? data.substring(str_index[0], str_index[1]) : "";
}
