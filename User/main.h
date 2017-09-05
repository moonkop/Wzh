#ifndef __MAIN_H
#define __MAIN_H
//#define TREASURE
#define TRAVELCAR
#include "devices\PhotoSwitch.h"
#include "preProcesser.h"
#include "devices\ADC.h"
#include "devices\lcd.h"
#include "devices\RCC.h"
#include "devices\sen2020.h"
#include "devices\TIM.h"
#include "devices\USART.h"
#include "devices\USART_DMA.h"
#include "devices\LED.h"
#include "common.h"
#include "stdint.h"
#include "task.h"
#include "drivers\motor.h"
#include "LCD_driver\LCD_print.h"
#include "track.h"
#include "drivers\buttonIR.h"
#include "devices\motorEncoder.h"
#include "LCD_driver\LCD_show.h"
#include "drivers\RespCom.h"
#include "devices\KEY.h"
#include "mainmap.h"
#include "ProcessFunctions.h"
#include "Beep.h"
#include "devices\CameraFlash.h"
#include "Actions.h"
#include "drivers\FlashOperation.h"
#include "devices\WS2811.h"
#include "Actions.h"
#include "myMath.h"
#include "Travel.h"
#include "Treasure.h"

void waitingForBegin();

int main(void);

#endif // !__MAIN_H

