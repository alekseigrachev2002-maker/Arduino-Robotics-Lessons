#define IN1 11  // пины левого мотора, ШИМ
#define IN2 6
#define IN3 5  // пины правого мотора, ШИМ
#define IN4 3

#define LEFT_SENS A0   // пин левого датчика линии
#define RIGHT_SENS A1  // пин правого датчика линии

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

void sensors() {
  int16_t left = analogRead(LEFT_SENS);
  int16_t right = analogRead(RIGHT_SENS);
  Serial.print(left);
  Serial.print(' ');
  Serial.print(right);
  Serial.print(' ');
  Serial.println(left - right);
  delay(10);
}

void followLine() {
  const int16_t speed = 150;
  const float kp = 0.0;  // TODO 3: при нулевом kd увеличивайте kp, пока робот не начнёт вписываться в поворот.
  const float kd = 0.0;  // TODO 4: сохраните kp и подберите kd, чтобы погасить раскачку.
  static int16_t errOld = 0;  // ошибка на предыдущем шаге

  int16_t err = analogRead(LEFT_SENS) - analogRead(RIGHT_SENS);

  // Для Д-составляющей находим изменение ошибки за один шаг.
  int16_t dErr = err - errOld;
  errOld = err;  // запоминаем ошибку для следующего шага

  // Управляющее воздействие: поправку прибавляем к скорости левого колеса
  // и вычитаем из скорости правого.
  float control = kp * err + kd * dErr;
  motors(speed + control, speed - control);
  delay(10);
}

void setup() {
  pinMode(IN1, OUTPUT);  // пины моторов в режиме OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // открываем монитор порта
}

void loop() {
  sensors();        // TODO 1: измерьте L, R и их разность на белом и чёрном.
  // followLine();  // TODO 2: включите движение по линии. При нулевых коэффициентах проверьте команды колёсам.
}
