#include <SoftwareSerial.h>

SoftwareSerial espSerial(11, 10);

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
}

void loop() {
  espSerial.println("Hello from ESP8266!");
  if (espSerial.available()) {
    String msg = espSerial.readStringUntil('\n');
    Serial.println(msg);
  }
  delay(2000);
}
