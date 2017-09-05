#ifndef __MOTOR_ENCODER_H
#define __MOTOR_ENCODER_H
#include "stm32f4xx.h"

void motorEncoder_init();

void attachCounterToEncoder(int * leftCounter, int * rightCounter);

void deattchCounterFromEncoder(int * leftCounter, int * rightCounter);

void deleteLeftCounter(int * counter);

void deleteRightCounter(int * counter);

void RightEncoderHandler(int num);

void LeftEncoderHandler(int num);











#endif // !__MOTOR_ENCODER_H

