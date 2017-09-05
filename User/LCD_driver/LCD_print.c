
#include "LCD_print.h"
#include "LCD_show.h"
#include "preProcesser.h"
#include "lcd.h"
#include <stdarg.h>


int currentChar = 0;
int currentLine = 0;
int bufferCount = 0;
char currentLineBuffer[25] = "";



//-----settings=----//

int bufferTop = 240;
int bufferleft = 0;
int bufferHeight = 100;
int bufferWitdh = 240;
//-----settings=----//




int heightPerChar = 0;
int widthPerChar = 0;
int bufferLines = 0;
int bufferwidthChar = 0;

extern u8 lcd_show_drawing_Flag;
bool LCD_USART_DEBUG = 1;


void LCD_Print_init()
{
	int charwidth = PRINTCHARSIZE / 2;
	currentChar = 0;
	currentLine = 0;
	switch (PRINTCHARSIZE)
	{
	case 12:
		bufferLines = bufferHeight / PRINTCHARSIZE;
		bufferwidthChar = bufferWitdh / charwidth;
		heightPerChar = 12;
		widthPerChar = 6;
		break;

	case 16:
		bufferLines = bufferHeight / PRINTCHARSIZE;
		bufferwidthChar = bufferWitdh / charwidth;
		heightPerChar = 16;
		widthPerChar = 8;
		break;
	case 24:
		bufferLines = bufferHeight / PRINTCHARSIZE;
		bufferwidthChar = bufferWitdh / charwidth;
		heightPerChar = 24;
		widthPerChar = 12;
		break;

	default:
		bufferLines = bufferHeight / PRINTCHARSIZE;
		bufferwidthChar = bufferWitdh / charwidth;
		heightPerChar = 12;
		widthPerChar = 6;
		break;
	}
}
void LCD_ClearLine()
{
	LCD_Fill_onecolor(bufferleft, bufferTop + currentLine*heightPerChar, bufferleft + bufferWitdh, bufferTop + (currentLine + 1)*heightPerChar, 0xffff);

	//刘文翔2017 7 16
	//在指定区域填充颜色1，2个是左上角x,y 3，4个是右下角x,y最后面的是颜色
	//bufferleft左边的距离bufferTop离顶部的距离currentline是现在已经有的行数heightPerChar每个字符的高度
	//bufferWitdh总的字符宽度
}
void _LCD_newLine()
{
	//currentLineBuffer[currentChar] = 0;
//	applendToBuffer(currentLineBuffer);

	currentLine++;//行数增加
	//换行
	currentChar = 0;//当前字符数量
	//
	bufferCount++;
	if (currentLine == bufferLines)//满溢时候为零
		currentLine = 0;

	LCD_ClearLine();  //换新的一行的时候我们需要知道下一行的左上角右下角的坐标
}
#define USART_DEBUG USART2
void USART_DEBUG_SEND(u8 data)
{
	u8 transmitCompleteFlag = USART_GetFlagStatus(USART_DEBUG, USART_FLAG_TC);

	if (transmitCompleteFlag == 0)
	{
		while (USART_GetFlagStatus(USART_DEBUG, USART_FLAG_TC) == RESET);
	}
	USART_ClearFlag(USART_DEBUG, USART_FLAG_TC);
	USART_SendData(USART_DEBUG, data);

	//USART_GetFlagStatus(USART_DEBUG, USART_FLAG_TC);
	//USART_SendData(USART_DEBUG, data);
	//while (USART_GetFlagStatus(USART_DEBUG, USART_FLAG_TC) == RESET);

}
void _LCD_Print_Putch(char ch)
{
	if (LCD_USART_DEBUG)
	{
		USART_DEBUG_SEND(ch);
	}
	if (currentChar > bufferwidthChar)//当现在的数量已经到达每行容纳字符的总数量的时候我们进行换行
	{
		_LCD_newLine();
	}
	//currentLineBuffer[currentChar] = ch;
	switch (ch)
	{
	case '\a':
		return;
	case '\b': currentChar--;
		return;
	case '\t': currentChar = (currentChar / 8 + 1) * 8;
		return;
	case '\n':
		_LCD_newLine();
		return;
	case '\v':
		return;
	case '\f':
		return;
	case '\r':
		_LCD_newLine();
		return;
	}

	LCD_DisplayChar(
		currentChar++ * widthPerChar + bufferleft,
		currentLine * heightPerChar + bufferTop,
		ch,
		PRINTCHARSIZE);
	//第一个函数是x坐标第二个是y的坐标第三个是什么字符地4个是字体的大小
	//currentChar当前字符的个数乘上每个字符的宽度加上左边的间距
	//每行的行数乘上每行的行高加上离顶部的距离
	//ch要显示的字符
	//PRINTCHARSIZE每个字符的bit数

}
void _LCD_Show_Putch(char ch, LCD_Show_Structure_Typedef * structure)
{



	LCD_DisplayChar(structure->left + structure->_currentOffset*structure->fontSize / 2, structure->top, ch, structure->fontSize);
	//structure是一个包含很多参数的结构体left是离左边的距离_currentOffset是当前的偏移量
	//然后和字体大小相乘除以2
	structure->_currentOffset++;//每调用一次偏移量加1

}
void LCD_putch(char ch, LCD_Show_Structure_Typedef * structure)
{
	if (structure)                //如果有structure调用_LCD_Show_Putch
	{
		_LCD_Show_Putch(ch, structure);
	}
	else                             //否则_LCD_Print_Putch
	{
		_LCD_Print_Putch(ch);
	}
}
void _LCD_printstr(void * ptr, LCD_Show_Structure_Typedef * structure)//打印字符串
{
	char* str = (char*)ptr;

	while (*str)
	{
		LCD_putch(*str++, structure);
	}
}
void _LCD_printDec(void *  ptr, LCD_Show_Structure_Typedef * structure)//打印10进制数
{
	int num = *(int *)ptr;
	if (num < 0)
	{
		num = -num;
		LCD_putch('-', structure);
	}
	char str[32] = "";
	int len = 0;
	do	str[len++] = num % 10 + 48; while (num /= 10);
	while (len--)	LCD_putch(str[len], structure);
}
void _LCD_printHex(void *  ptr, LCD_Show_Structure_Typedef * structure)//打印16进制
{
	int hex = *(int *)ptr;
	char str[20] = "";
	int len = 0;
	do
	{
		str[len++] = hex & 0x0f;
	} while (hex >>= 4);
	while (len--)
	{
		if (str[len] < 10)
		{
			LCD_putch(str[len] + 48, structure);

		}
		else
		{
			LCD_putch(str[len] - 10 + 65, structure);
		}
	}
}
void _LCD_printBin(void *  ptr, LCD_Show_Structure_Typedef * structure)//打印2进制
{
	int bin = *(int *)ptr;
	char str[32] = "";
	int len = 0;
	do
	{
		str[len++] = bin & 0x01;
	} while (bin >>= 1);
	while (len--)
	{
		LCD_putch(str[len] + 48, structure);
	}
}
void _LCD_printFloat(void *  ptr, LCD_Show_Structure_Typedef * structure)//打印浮点数
{
	double num = *(double *)ptr;
	int numInt = (int)num;
	_LCD_printDec(&numInt, structure);
	num -= numInt;
	LCD_putch('.', structure);
	int num1 = num * 1000;

	_LCD_printDec((void*)&num1, structure);
}

void LCD_printf(char* fmt, ...)
{
	double varFloat = 0;
	int varInt = 0;
	char* varStr = NULL;
	char varCh = 0;
	va_list vp;
	char * pfmt = NULL;
	va_start(vp, fmt);
	pfmt = fmt;

	while (*pfmt)
	{
		if (*pfmt == '%')       //模拟print输出
		{
			switch (*(++pfmt))
			{
			case 'c':             //c输出的是char
				varCh = va_arg(vp, int);
				LCD_putch(varCh, 0);
				break;

			case 'd':
			case 'i':
				varInt = va_arg(vp, int);
				LCD_printDec(varInt);
				break;

			case 'f':
				varFloat = va_arg(vp, double);
				LCD_printFloat(varFloat);
				break;
			case 's':
				varStr = va_arg(vp, char*);
				LCD_printstr(varStr);
				break;
			case 'b':
			case 'B':
				varInt = va_arg(vp, int);
				LCD_printBin(varInt);
				break;
			case 'x':
			case 'X':
				varInt = va_arg(vp, int);
				LCD_printHex(varInt);
				break;

			case '%':
				LCD_putch('%', 0);
				break;
			}
			pfmt++;
		}
		else                                 //如果不是上面的情况打印字符
		{
			LCD_putch(*pfmt++, 0);
		}
	}
}



