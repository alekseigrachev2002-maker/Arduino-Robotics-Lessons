// robot-test.h — тесты робота: моторы (драйвер MX1508), датчики линии, дальномер HC-SR04.
// Лежит в одной папке с lesson-00-robot-test.ino, Arduino IDE открывает его соседней вкладкой.

#pragma once         // файл подключается только один раз
#include <Arduino.h>

#define IN1 3  // пины левого мотора, ШИМ
#define IN2 5
#define IN3 6  // пины правого мотора, ШИМ
#define IN4 11

#define LEFT_SENS A0   // пин левого датчика линии
#define RIGHT_SENS A1  // пин правого датчика линии

#define TRIG 12  // пины дальномера HC-SR04 (проверьте по схеме своего робота)
#define ECHO 13

void robotInit() {  // настройка пинов и монитора порта - вызвать первой строкой в setup()
  pinMode(IN1, OUTPUT);  // пины моторов в режиме OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);  // TRIG - запускаем измерение
  pinMode(ECHO, INPUT);   // ECHO - слушаем ответ

  Serial.begin(9600);  // открываем монитор порта
}

void motors(int16_t speed1, int16_t speed2) {  // двигаться (левый мотор, правый мотор)
  speed1 = constrain(speed1, -255, 255);       // сначала ограничиваем скорость от -255 до 255
  speed2 = constrain(speed2, -255, 255);

  if (speed1 > 0) {  // подаем speed1 на пины первого мотора
    analogWrite(IN1, speed1);
    analogWrite(IN2, 0);
  } else {
    analogWrite(IN1, 0);
    analogWrite(IN2, -speed1);
  }

  if (speed2 > 0) {  // подаем speed2 на пины второго мотора
    analogWrite(IN3, speed2);
    analogWrite(IN4, 0);
  } else {
    analogWrite(IN3, 0);
    analogWrite(IN4, -speed2);
  }
}

// ---------- тесты для setup(): выполняются один раз ----------

void wheelsTest() {  // каждое колесо вперед и назад по 1 секунде, потом оба вперед
  Serial.println("левое вперед");
  motors(150, 0);
  delay(1000);

  Serial.println("левое назад");
  motors(-150, 0);
  delay(1000);

  Serial.println("правое вперед");
  motors(0, 150);
  delay(1000);

  Serial.println("правое назад");
  motors(0, -150);
  delay(1000);

  Serial.println("оба вперед");
  motors(150, 150);
  delay(1000);

  motors(0, 0);
  Serial.println("стоп");
}

void startTest() {  // ШИМ растет на 10 каждую секунду: запишите, при каком ШИМ поехало каждое колесо
  for (int16_t pwm = 0; pwm <= 250; pwm = pwm + 10) {
    Serial.print("ШИМ ");
    Serial.println(pwm);
    motors(pwm, pwm);
    delay(1000);
  }
  motors(0, 0);
  Serial.println("стоп");
}

void driveTest(int16_t pwm, uint32_t time) {  // ждем 3 секунды, едем time миллисекунд с ШИМ pwm, выключаем моторы
  delay(3000);  // время, чтобы поставить робота на трек и убрать руки
  motors(pwm, pwm);
  delay(time);
  motors(0, 0);  // моторы выключены, робот докатывается сам
}

// ---------- тесты для loop(): печатают одну строку ----------

void lineSensors() {  // левый датчик, правый датчик и их разность
  int16_t left = analogRead(LEFT_SENS);
  int16_t right = analogRead(RIGHT_SENS);
  Serial.print(left);
  Serial.print(" ");
  Serial.print(right);
  Serial.print(" ");
  Serial.println(left - right);
}

void distance() {  // расстояние до препятствия в сантиметрах
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  // импульс 10 мкс запускает измерение
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  uint32_t duration = pulseIn(ECHO, HIGH, 30000);  // время эха, мкс; ждем не дольше 30 мс, нет эха - 0
  Serial.print("см ");
  Serial.println(duration / 58);  // звук проходит 1 см туда и обратно примерно за 58 мкс
}
