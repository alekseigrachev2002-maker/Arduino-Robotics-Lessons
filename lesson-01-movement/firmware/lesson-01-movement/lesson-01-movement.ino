#define IN1 11  // пины левого мотора, ШИМ
#define IN2 6
#define IN3 5  // пины правого мотора, ШИМ
#define IN4 3

void motors(int16_t speed1, int16_t speed2) {  // первый аргумент управляет левым мотором, второй — правым
  speed1 = constrain(speed1, -255, 255);       // ограничиваем команду диапазоном от -255 до 255
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

void setup() {
  pinMode(IN1, OUTPUT);  // настраиваем пины управления моторами как выходы
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // задаем скорость обмена с монитором порта
  motors(0, 0);
}

void loop() {
  // TODO 1: подберите ШИМ колес для движения по прямой.
  // TODO 2: подберите длительность поворота на месте на 90°.
  // TODO 3 (дополнительно): проедьте по квадрату и сравните точку остановки со стартом.
}
