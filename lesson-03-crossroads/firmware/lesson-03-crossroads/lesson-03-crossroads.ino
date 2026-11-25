#include "robot.h"

void followLine() {
  const int speed = 150;
  const float kp = 0.1;  // начните с проверки знака
  const float kd = 0.0;
  static int errOld = 0;

  int err = analogRead(A0) - analogRead(A1);
  float control = kp * err + kd * (err - errOld);
  motors(speed + control, speed - control);
  errOld = err;
}

// Перенесите свои kp и kd. Добавьте интеграл, счётчик въездов и остановку.
void setup() {
  robotInit();
}

void loop() {
  followLine();
  delay(10);
}
