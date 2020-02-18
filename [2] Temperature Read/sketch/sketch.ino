/*
 * NSM Cansat Bootcamp
 * Temperature Read (Celsius / Farenheit)
 */

#include <DHT.h>;

int dht_input_pin 7
#define dhttype DHT22
DHT dht(dht_input_pin, dhttype); 

int chk;
float temp;

void setup() {
  
  Serial.begin(115200); 
  dht.begin();
  
}

void loop() {
  
  delay(5000);

  temp = dht.readTemperature();

  Serial.print("Sending Temperature...");
  delay(1000);
  Serial.print(temp);
  Serial.println(" Celsius");

}
