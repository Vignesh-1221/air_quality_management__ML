/*
Air Quality Management System – Arduino Firmware

Final controller firmware used during the project.
Controls fan and blower based on CO sensor readings.
ML prediction logic runs off-device.
*/

#include <ESP8266WiFi.h>

#define MOTOR_ENABLE_PIN D1
#define MOTOR_INPUT1_PIN D2
#define MOTOR_INPUT2_PIN D3
#define BLOWER_INPUT1_PIN D6
#define BLOWER_INPUT2_PIN D7
#define CO_SENSOR_PIN A0

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

float motorThreshold = 50.0;
float blowerThreshold = 100.0;

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_INPUT1_PIN, OUTPUT);
  pinMode(MOTOR_INPUT2_PIN, OUTPUT);
  pinMode(BLOWER_INPUT1_PIN, OUTPUT);
  pinMode(BLOWER_INPUT2_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  float sensorValue = analogRead(CO_SENSOR_PIN);
  float normalizedValue = (sensorValue / 1024.0) * 100.0;

  Serial.print("CO Level: ");
  Serial.println(normalizedValue);

  if (normalizedValue <= motorThreshold) {
    runMotor();
    stopBlower();
  } else if (normalizedValue <= blowerThreshold) {
    stopMotor();
    runBlower();
  } else {
    stopMotor();
    stopBlower();
  }

  delay(1000);
}

void stopMotor() {
  digitalWrite(MOTOR_ENABLE_PIN, LOW);
  digitalWrite(MOTOR_INPUT1_PIN, LOW);
  digitalWrite(MOTOR_INPUT2_PIN, LOW);
}

void runMotor() {
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(MOTOR_INPUT1_PIN, HIGH);
  digitalWrite(MOTOR_INPUT2_PIN, LOW);
}

void stopBlower() {
  digitalWrite(BLOWER_INPUT1_PIN, LOW);
  digitalWrite(BLOWER_INPUT2_PIN, LOW);
}

void runBlower() {
  digitalWrite(BLOWER_INPUT1_PIN, HIGH);
  digitalWrite(BLOWER_INPUT2_PIN, LOW);
}
