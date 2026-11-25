#include "robot.h"

void followLine() {
  int err = analogRead(LEFT_SENS) - analogRead(RIGHT_SENS);
  // Проверьте знак ошибки в плоттере. Затем замените вывод шагом ПД из урока.
  Serial.println(err);
}

void setup() {
  robotInit();
}

void loop() {
  followLine();
  delay(10);
}
