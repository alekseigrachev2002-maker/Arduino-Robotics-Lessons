#pragma once
#include <Arduino.h>

#define IN1 11  // пины левого мотора, ШИМ
#define IN2 6
#define IN3 5  // пины правого мотора, ШИМ
#define IN4 3

#define LEFT_SENS A0   // пин левого датчика линии
#define RIGHT_SENS A1  // пин правого датчика линии

#define TRIG 12  // цифровые пины HC-SR04: в этом курсе TRIG — D12, ECHO — D13
#define ECHO 13

void motors(int16_t speed1, int16_t speed2);
void wheelsTest();
void startTest();
void driveTest(int16_t pwm, uint32_t time);
void lineSensors();
void distance();
