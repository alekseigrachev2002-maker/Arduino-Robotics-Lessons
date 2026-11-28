#define IN1 11  // пины левого мотора, ШИМ
#define IN2 6
#define IN3 5  // пины правого мотора, ШИМ
#define IN4 3

#define LEFT_SENS A0   // пин левого датчика линии
#define RIGHT_SENS A1  // пин правого датчика линии

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

void followLine() {
  // TODO 1: перенесите настройки ПД из урока 02 и подберите ki на длинной дуге.
  const int16_t speed = 150;
  const float kp = 0.0;
  const float kd = 0.0;
  const float ki = 0.0;
  static int16_t errOld = 0;    // ошибка на предыдущем шаге
  static float integral = 0.0;  // сумма ошибок с начала заезда

  // Ошибка положения: показание левого датчика минус показание правого.
  int16_t err = analogRead(LEFT_SENS) - analogRead(RIGHT_SENS);

  // Для Д-составляющей находим изменение ошибки, для И-составляющей накапливаем сумму.
  int16_t dErr = err - errOld;
  errOld = err;
  integral = integral + err;
  integral = constrain(integral, -25000.0, 25000.0);  // предел при ki = 0.002

  // Управляющее воздействие складывается из трех составляющих: П, И и Д.
  float control = kp * err + ki * integral + kd * dErr;
  int16_t left = constrain(speed + control, -255, 255);
  int16_t right = constrain(speed - control, -255, 255);
  motors(left, right);
  delay(10);
}

uint16_t crossRoad() {
  const int16_t threshold = 500;  // TODO 2: выберите порог черного по измерениям обоих датчиков.
  uint16_t count = 0;
  static bool wasCross = false;
  bool isCross = analogRead(LEFT_SENS) < threshold && analogRead(RIGHT_SENS) < threshold;
  // TODO 3: исправьте три ошибки в счетчике. Один въезд — один отсчет.
  if (isCross) {
    count = count + 1;
  }
  return count;
}

void setup() {
  pinMode(IN1, OUTPUT);  // настраиваем пины управления моторами как выходы
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // задаем скорость обмена с монитором порта
}

void loop() {
  uint16_t crossings = crossRoad();
  // Serial.println(crossings);  // для проверки счетчика на столе
  // TODO 4: остановитесь на пятом перекрестке и сохраняйте остановку.
  followLine();
}
