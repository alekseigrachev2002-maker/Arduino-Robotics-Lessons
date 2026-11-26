// ТЕСТ РОБОТА: моторы, датчики линии, дальномер HC-SR04.
// Реализация тестов - во вкладке robot-test.cpp. Нужный тест раскомментировать.
// Монитор порта: 9600.

#include "robot-test.h"

void setup() {
  pinMode(IN1, OUTPUT);  // пины моторов в режиме OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);  // TRIG - запускаем измерение
  pinMode(ECHO, INPUT);   // ECHO - слушаем ответ

  Serial.begin(9600);  // открываем монитор порта

  wheelsTest();          // TODO 1: колеса по очереди: левое вперед и назад, правое вперед и назад, оба вперед
  // startTest();           // TODO 2: плавный разгон: при каком ШИМ колеса начинают крутиться
  // driveTest(150, 2000);  // TODO 3: заезд по треку без кабеля: ШИМ 150, 2000 мс
}

void loop() {
  static uint32_t lastTime = 0;
  if (millis() - lastTime >= 100) {  // раз в 100 мс, не останавливая программу
    lastTime = millis();
    // lineSensors();  // TODO 4: датчики линии: левый, правый, разность
    // distance();     // TODO 4: дальномер: расстояние, см
  }
}
