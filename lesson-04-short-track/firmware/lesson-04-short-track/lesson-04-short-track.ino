#include "robot.h"

unsigned long distanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, 30000) / 58;
}

void setup() {
  robotInit();
}

void loop() {
  // Начните с измерений перед гранью кубика и в свободном направлении.
  Serial.println(distanceCm());
  delay(100);
  // Затем добавьте свои followLine(), crossRoad() и выбор пути на развилке.
}
