
/*
 * Урок 3: Подсчет количества перекрестков
 */

#define IN1 6  // пины правого мотора, ШИМ
#define IN2 11
#define IN3 3  // пины левого мотора, ШИМ
#define IN4 5

#define LEFT_SENS A0   // левый датчик линии
#define RIGHT_SENS A1  // правый

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void followLine() {

  const float speed = 150;          // Шаг 1: Базовая скорость (от 0 до 255)
  const float sensorBalance = 1.0;  // Шаг 2: Балансировка датчиков
  const float kp = 0.3;             // Шаг 3: Настрой П-коэффициент (отвечает за резкость поворота)
  const float kd = 0.05;            // Шаг 4: Настрой Д-коэффициент (гасит колебания)

  static float errOld = 0.0;  // память о прошлой ошибке
  // 1. Считаем текущую ошибку (разницу между показаниями датчиков)
  float err = (analogRead(LEFT_SENS) * sensorBalance) - analogRead(RIGHT_SENS);
  // 2. Считаем управляющее воздействие (П-часть + Д-часть)
  float control = (err * kp) + ((err - errOld) * kd);
  // 3. Передаем команду на моторы: один ускоряем, другой замедляем
  motors(speed - control, speed + control);
  // 4. Запоминаем текущую ошибку для следующего цикла
  errOld = err;
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

  if (speed2 > 0) {  // подаем speed2 на пины вторго мотора
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
  Serial.println(analogRead(RIGHT_SENS) - analogRead(LEFT_SENS));
}

void loop() {
  followLine();
  sensors();
}
