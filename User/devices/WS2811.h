#ifndef _WS2811_H
#define	_WS2811_H

#include "stm32f4xx.h"
#define nWs 12		// 有多少颗WS2811级联（个人认为也可以是闪烁）
extern unsigned long WsDat[];

extern unsigned long Color_red;
extern unsigned long Color_green;
extern unsigned long Color_blue;
extern unsigned long Color_pink;
extern unsigned long Color_purple;
extern unsigned long Color_yellow;
extern unsigned long Color_cyan;
extern unsigned long Color_white;

/*******************Just pay attention to these four functions:**************************/

/*1.	Initialize the SPI,DMA and GPIO (A7)*/

/*2.	Set colors and priorities ,0xFF0000 is Red,0x00FF00 is Green ,ox0000FF is blue.
			And the smaller the number, the higher the priority*/
			
/*3.	Select the highest priority display in the color.Then clear all the colors*/

/*4.	breathing light*/

void LED_SPI_LowLevel_Init(void);
void SetColor_Priority(int color,int priority);
void WS2811_Update(void);
void WS2811_Breath(void);//渐变呼吸



void WS2811_Update_Color();
void WS_SetAll(void);
void LED_SPI_WriteByte(uint16_t Data);
void LED_SPI_SendBits(uint8_t bits);
void LED_SPI_SendPixel(uint32_t color);
void LED_SPI_Update(unsigned long buffer[], uint32_t length);
void setPixelColor(unsigned long buffer);
#endif /* __LED_H */
