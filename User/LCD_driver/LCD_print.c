
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

	//������2017 7 16
	//��ָ�����������ɫ1��2�������Ͻ�x,y 3��4�������½�x,y����������ɫ
	//bufferleft��ߵľ���bufferTop�붥���ľ���currentline�������Ѿ��е�����heightPerCharÿ���ַ��ĸ߶�
	//bufferWitdh�ܵ��ַ����
}
void _LCD_newLine()
{
	//currentLineBuffer[currentChar] = 0;
//	applendToBuffer(currentLineBuffer);

	currentLine++;//��������
	//����
	currentChar = 0;//��ǰ�ַ�����
	//
	bufferCount++;
	if (currentLine == bufferLines)//����ʱ��Ϊ��
		currentLine = 0;

	LCD_ClearLine();  //���µ�һ�е�ʱ��������Ҫ֪����һ�е����Ͻ����½ǵ�����
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
	if (currentChar > bufferwidthChar)//�����ڵ������Ѿ�����ÿ�������ַ�����������ʱ�����ǽ��л���
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
	//��һ��������x����ڶ�����y�������������ʲô�ַ���4��������Ĵ�С
	//currentChar��ǰ�ַ��ĸ�������ÿ���ַ��Ŀ�ȼ�����ߵļ��
	//ÿ�е���������ÿ�е��и߼����붥���ľ���
	//chҪ��ʾ���ַ�
	//PRINTCHARSIZEÿ���ַ���bit��

}
void _LCD_Show_Putch(char ch, LCD_Show_Structure_Typedef * structure)
{



	LCD_DisplayChar(structure->left + structure->_currentOffset*structure->fontSize / 2, structure->top, ch, structure->fontSize);
	//structure��һ�������ܶ�����Ľṹ��left������ߵľ���_currentOffset�ǵ�ǰ��ƫ����
	//Ȼ��������С��˳���2
	structure->_currentOffset++;//ÿ����һ��ƫ������1

}
void LCD_putch(char ch, LCD_Show_Structure_Typedef * structure)
{
	if (structure)                //�����structure����_LCD_Show_Putch
	{
		_LCD_Show_Putch(ch, structure);
	}
	else                             //����_LCD_Print_Putch
	{
		_LCD_Print_Putch(ch);
	}
}
void _LCD_printstr(void * ptr, LCD_Show_Structure_Typedef * structure)//��ӡ�ַ���
{
	char* str = (char*)ptr;

	while (*str)
	{
		LCD_putch(*str++, structure);
	}
}
void _LCD_printDec(void *  ptr, LCD_Show_Structure_Typedef * structure)//��ӡ10������
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
void _LCD_printHex(void *  ptr, LCD_Show_Structure_Typedef * structure)//��ӡ16����
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
void _LCD_printBin(void *  ptr, LCD_Show_Structure_Typedef * structure)//��ӡ2����
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
void _LCD_printFloat(void *  ptr, LCD_Show_Structure_Typedef * structure)//��ӡ������
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
		if (*pfmt == '%')       //ģ��print���
		{
			switch (*(++pfmt))
			{
			case 'c':             //c�������char
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
		else                                 //�����������������ӡ�ַ�
		{
			LCD_putch(*pfmt++, 0);
		}
	}
}



