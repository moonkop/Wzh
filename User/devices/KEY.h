#ifndef __KEY_H
#define __KEY_H
#include "stm32f4xx.h"

//����IO�˿ڶ���
#define KEY0 		PFin(9)   
#define KEY1 		PFin(8)		
#define KEY2 		PFin(7)		
#define KEY3 	  PFin(6)		


//����ֵ����
#define KEY0_DATA	  1
#define KEY1_DATA	  2
#define KEY2_DATA	  3
#define KEY3_DATA     4

//��������

extern int Click_Is_Down;

	      //IO��ʼ��
void KEY_IT_init();

u8 KeyFitter();

void KeyFitterClear();

void Click_Switch_Init();

u8 Click_Triggered();

void Test_getClick_TriggeredData();


#endif
