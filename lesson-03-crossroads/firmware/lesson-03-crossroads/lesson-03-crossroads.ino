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

void followLine() {
  const int16_t speed = 150;
  // TODO 1: перенесите свои kp, kd и шаг цикла. Добавьте накопление ошибки и ki.
  const float kp = 0.1;  // начните с проверки знака
  const float kd = 0.0;
  static int16_t errOld = 0;  // ошибка на предыдущем шаге

  // Ошибка положения: показание левого датчика минус показание правого.
  int16_t err = analogRead(LEFT_SENS) - analogRead(RIGHT_SENS);

  // Для Д-составляющей находим изменение ошибки за один шаг.
  int16_t dErr = err - errOld;
  // TODO 1: здесь прибавьте текущую ошибку к накопленной сумме.
  errOld = err;  // запоминаем ошибку для следующего шага

  // Управляющее воздействие: поправку прибавляем к скорости левого колеса
  // и вычитаем из скорости правого.
  float control = kp * err + kd * dErr;
  motors(speed + control, speed - control);
  delay(10);
}

uint16_t crossRoad() {
  const int16_t threshold = 500;  // TODO 2: подставьте порог из своих измерений.
  static uint16_t count = 0;
  static bool wasCross = false;
  bool isCross = analogRead(LEFT_SENS) < threshold && analogRead(RIGHT_SENS) < threshold;
  // TODO 3: прибавьте единицу при въезде и запомните isCross перед выходом.
  return count;
}

void setup() {
  pinMode(IN1, OUTPUT);  // пины моторов в режиме OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // открываем монитор порта
}

void loop() {
  uint16_t crossings = crossRoad();
  // Serial.println(crossings);  // TODO 3: для проверки на столе замените followLine() на motors(0, 0).
  // TODO 4: при crossings >= 5 остановите моторы и пропустите followLine().
  followLine();
}
