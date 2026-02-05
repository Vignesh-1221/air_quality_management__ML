int motorPin1 = 4;
int motorPin2 = 5;
int blowerPin1 = 9;
int blowerPin2 = 10;
const int sensorPin = A0;
float thresholdValue = 30.0;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(blowerPin1, OUTPUT);
  pinMode(blowerPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  float normalizedValue = (sensorValue / 1024.0) * 100.0;

  if (normalizedValue < thresholdValue) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(blowerPin1, LOW);
    digitalWrite(blowerPin2, LOW);
  } else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(blowerPin1, HIGH);
    digitalWrite(blowerPin2, LOW);
  }

  delay(1000);
}
