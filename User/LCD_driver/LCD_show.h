#ifndef __LCD_SHOW_H
#define __LCD_SHOW_H

#include "stm32f4xx.h"
#include "../bsp_flash.h"
#define ACCESS_LVL_READ 0x01
#define ACCESS_LVL_READWRITE 0x03
#define ACCESS_LVL_READWRITEFLASH 0x07

typedef struct _LCD_Show_Structure LCD_Show_Structure_Typedef;

typedef struct  _LCD_Show_Structure
{
	u16 top;
	u16 left;
	u16 widthChar;
	u16 _width;
	u8 fontSize;
	u8 _fontWidth;
	u8 accessLvl;
	int ChangeStep;
	
	char * name;
	int _namelength;
	int * dataPtr;
	void *  voiddataptr;
	u8 showBorder;
	void (*showFunction)(void *, LCD_Show_Structure_Typedef * );
	void(*LeftFunction)(void);
	void(*RightFunction)(void);
	void(*refreshFunction)(void);

	int _currentOffset;
	

	LCD_Show_Structure_Typedef ** children;
	LCD_Show_Structure_Typedef	* parent;
	int maxChildCount;
	int currentChildCount;
	


} LCD_Show_Structure_Typedef;

extern LCD_Show_Structure_Typedef * LCD_Show_Structures[];
extern int LCD_Show_Structure_Count;
extern int LCD_Selected_Index;
extern unsigned short values[20];

void LCD_Show_User_Config();

void LCD_Show_Init();

//void READ_FLASH_VALUE(void);


LCD_Show_Structure_Typedef * LCD_DEBUG_Premeter_Add(int * premeter, char * name, int AccessLvl, LCD_Show_Structure_Typedef * parent);

LCD_Show_Structure_Typedef * LCD_DEBUG_Function_Add(char * name, void(*leftFunction)(void), LCD_Show_Structure_Typedef * parent);

LCD_Show_Structure_Typedef * LCD_DEBUG_Node_Add(char * name, int childCount, LCD_Show_Structure_Typedef * parent );

LCD_Show_Structure_Typedef * LCD_DEBUG_Add_As_Child(int * premeter, char * name, int childCount, LCD_Show_Structure_Typedef * parent);

void LCD_Add_To_Node(LCD_Show_Structure_Typedef * parent, LCD_Show_Structure_Typedef * child);


LCD_Show_Structure_Typedef * _LCD_Show_Structure_Add(int * dataPtr, u8 fontsize, u16 top, u16 left, u16 widthChar, char * name, u8 showBorder, void(*showFunction)(void *, LCD_Show_Structure_Typedef *));

void LCD_Show();

void LCD_Show_Tree(LCD_Show_Structure_Typedef * lcd);

void LCD_NextNode(LCD_Show_Structure_Typedef * currentNode);

void LCD_GoBack();

void LCD_Show_Clear();

LCD_Show_Structure_Typedef * LCD_Get_Current_Selected_Node();

void _LCD_Structure_Show(LCD_Show_Structure_Typedef * lcd);

void LCD_Show_PutCh(char ch, int charIndex, LCD_Show_Structure_Typedef * currentLcd);



void LCD_Structure_Calc_Postion();


void _LCD_Show_Clear_Area(LCD_Show_Structure_Typedef * lcd);

void _LCD_Show_Draw_Border(LCD_Show_Structure_Typedef * lcd);

void _LCD_Clear_Border(LCD_Show_Structure_Typedef * lcd);

void _GET_LCD_VALUES(void);

void _LCD_DEBUG_KEY_DOWN();

void _LCD_DEBUG_KEY_UP();

void _LCD_DEBUG_KEY_LEFT();

void _LCD_DEBUG_KEY_RIGHT();

#endif // !__LCD_SHOW_H
