#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f4xx.h"
void Beep_init();

void BeepOn();

void BeepOff();

void beepCheck();

void beepWaiting(int time);

#endif

