#pragma once
#include <Arduino.h>

void robotInit();
void motors(int16_t speed1, int16_t speed2);
void wheelsTest();
void startTest();
void driveTest(int16_t pwm, uint32_t time);
void lineSensors();
void distance();
