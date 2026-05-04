// УРОК 3: подсчет количества перекрестков

#define IN1 3  // пины левого мотора, ШИМ
#define IN2 5
#define IN3 6  // пины правого мотора, ШИМ
#define IN4 11

#define LEFT_SENS A0   // пин левого датчика
#define RIGHT_SENS A1  // пин правого  датчика

#define TRESHOLD 300  // условие перекрестка: слева и справа темная линия

void setup() {
  pinMode(IN1, OUTPUT);  // все пины в режиме работы OUTPUT - управляем нагрузкой
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // открываем монитор порта
}

void motors(int16_t speed1, int16_t speed2) {  // функция движения с первого урока
  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);

  if (speed1 > 0) {
    analogWrite(IN1, speed1);
    analogWrite(IN2, 0);
  } else {
    analogWrite(IN1, 0);
    analogWrite(IN2, -speed1);
  }

  if (speed2 > 0) {
    analogWrite(IN3, speed2);
    analogWrite(IN4, 0);
  } else {
    analogWrite(IN3, 0);
    analogWrite(IN4, -speed2);
  }
}

void sensors() {  // печатаем данные с левого и правого датчика для настройки
  Serial.print(analogRead(LEFT_SENS));
  Serial.print(" ");
  Serial.print(analogRead(RIGHT_SENS));
  Serial.print(" ");
  Serial.println(analogRead(LEFT_SENS) - analogRead(RIGHT_SENS));
}

void followLine() {  // движение по линии

  const float speed = 150;          // Шаг 1: Базовая скорость (от 0 до 255)
  const float sensorBalance = 1.0;  // Шаг 2: Балансировка датчиков (если их показания отличаются)
  const float kp = 0.3;             // Шаг 3: Настрой П-коэффициент (отвечает за резкость поворота)
  const float kd = 0.05;            // Шаг 4: Настрой Д-коэффициент (гасит колебания)

  static float errOld = 0.0;  // память о прошлой ошибке
  // 1. Считаем текущую ошибку (разницу между показаниями датчиков)
  float err = (analogRead(LEFT_SENS) * sensorBalance) - analogRead(RIGHT_SENS);
  // 2. Считаем управляющее воздействие (П-часть + Д-часть)
  float control = err * kp + (err - errOld) * kd;
  // 3. Передаем команду на моторы: один ускоряем, другой замедляем
  motors(speed - control, speed + control);
  // 4. Запоминаем текущую ошибку для следующего цикла
  errOld = err;
}

uint8_t crossRoad() {
  bool isCross = (analogRead(LEFT_SENS) < TRESHOLD && analogRead(RIGHT_SENS) < TRESHOLD);  // проверяем, что слева и справа темно

  static bool wasCross = false;  // логический флаг, который позволит отличить ситуацию, когда мы едем по перекрестку, от момента когда на него только заехали
  uint8_t count = 0;             // в этой строчке есть ошибка

  if (isCross) count = count + 1;  // и в этой тоже
                                   // а здесь чего-то не хватает
  return count;
}

void loop() {
  // sensors();
  uint8_t crossCount = crossRoad();

  // TODO: напишите код, чтобы робот ехал по линии (followLine)
  // и остановился, когда crossCount достигнет 5.
}
