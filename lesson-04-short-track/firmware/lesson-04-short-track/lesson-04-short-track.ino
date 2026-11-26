#define IN1 11  // пины левого мотора, ШИМ
#define IN2 6
#define IN3 5  // пины правого мотора, ШИМ
#define IN4 3

#define LEFT_SENS A0   // пин левого датчика линии
#define RIGHT_SENS A1  // пин правого датчика линии

#define TRIG 12  // цифровые пины HC-SR04: в этом курсе TRIG — D12, ECHO — D13
#define ECHO 13

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

float distanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  uint32_t duration = pulseIn(ECHO, HIGH, 30000);  // длительность эха в мкс
  return duration * 343.0 / (2.0 * 10000.0);
}

void setup() {
  pinMode(IN1, OUTPUT);  // пины моторов в режиме OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);  // TRIG - запускаем измерение
  pinMode(ECHO, INPUT);   // ECHO - слушаем ответ

  Serial.begin(9600);  // открываем монитор порта
}

void loop() {
  // TODO 1: подберите порог обнаружения кубика на неподвижном роботе.
  Serial.println(distanceCm());
  delay(100);

  // TODO 2: перенесите свои followLine() и crossRoad() с настройками из урока 03.
  // Замените диагностику движением по часовой стрелке до остановки на первом X.
  // TODO 3: проверьте три направления и выберите ветвь по положению кубика.
  // TODO 4: после выезда с X считайте перекрёстки и остановитесь на финише.
  // TODO 5: проверьте одну программу в трёх заездах: кубик слева, справа и без кубика.
}
