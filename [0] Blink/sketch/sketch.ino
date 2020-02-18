/*
 * NSM Cansat Bootcamp
 * Blink
 */

int output_pin = 13;

void setup() {
  
  pinMode(output_pin, OUTPUT);
  
}

void loop() {
  
  digitalWrite(output_pin, HIGH);   
  delay(1000);                       
  digitalWrite(output_pin, LOW);    
  delay(1000);                      

}
