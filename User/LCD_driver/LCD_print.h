#ifndef __LCD_PRINT_H
#define __LCD_PRINT_H
#include "stm32f4xx.h"
#include "LCD_show.h"
#define  PRINTCHARSIZE 12

#define HEIGHT 320
#define WIDTH 240
#define LCD_printstr(val)	_LCD_printstr(&val,NULL)
#define LCD_printDec(val)	_LCD_printDec(&val,NULL)
#define LCD_printHex(val)	_LCD_printHex(&val,NULL)
#define LCD_printBin(val)	_LCD_printBin(&val,NULL)
#define LCD_printFloat(val) _LCD_printFloat(&val,NULL)

void LCD_Print_init();

void _LCD_newLine();

void USART_DEBUG_SEND(u8 data);

void LCD_putch(char ch, LCD_Show_Structure_Typedef * structure);

void _LCD_printstr(void *  str, LCD_Show_Structure_Typedef * structure);

void _LCD_printDec(void *  num, LCD_Show_Structure_Typedef * structure);

void _LCD_printHex(void *  hex, LCD_Show_Structure_Typedef * structure);

void _LCD_printBin(void *  bin, LCD_Show_Structure_Typedef * structure);

void _LCD_printFloat(void *  num, LCD_Show_Structure_Typedef * structure);






	void LCD_printf(char * fmt, ...);






#endif // !__LCD_PRINT_H
