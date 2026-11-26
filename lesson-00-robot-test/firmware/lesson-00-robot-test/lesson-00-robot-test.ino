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

  wheelsTest();          // TODO 1: сверьте названия колёс и направления вращения с выводом в порт.
  // startTest();           // TODO 2: запишите ШИМ, при котором трогается каждое колесо.
  // driveTest(150, 2000);  // TODO 3: проверьте на полу, куда уводит робота и сколько он докатывается.
}

void loop() {
  static uint32_t lastTime = 0;
  if (millis() - lastTime >= 100) {  // раз в 100 мс, не останавливая программу
    lastTime = millis();
    // lineSensors();  // TODO 4: проверьте левый и правый датчики линии по очереди.
    // distance();     // TODO 4: проверьте, как меняется расстояние при удалении кубика.
  }
}
