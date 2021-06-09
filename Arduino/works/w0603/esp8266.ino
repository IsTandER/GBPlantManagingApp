#include <SoftwareSerial.h>
#define BT_RXD 2 
#define BT_TXD 3 
SoftwareSerial ESP_wifi(BT_RXD, BT_TXD);



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ESP_wifi.begin(9660);
ESP_wifi.setTimeout(5000);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  ESP.wifi.write(Serial.read());
}
if (ESP_wifi.available()){
  Serial.write(ESP.wifi.read());
}
 }
