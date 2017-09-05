#include "LCD_show.h"
#include "LCD_print.h"
#include "stdlib.h"
#include "lcd.h"
#include "preProcesser.h"
#include "main.h"
#include "stm32f4xx_tim.h"
#include "string.h"
#include "../ProcessFunctions.h"
#include "../devices/PhotoSwitch.h"

#include "../drivers/FlashOperation.h"
#include "../devices/CameraFlash.h"
#include "../Flash_driver/Flash.h"
/**********settings***********/
#define LCD_DEBUG_SHOW_CHAR_SIZE 12

/**********settings***********/

LCD_Show_Structure_Typedef* LCD_Show_Structures[100];
LCD_Show_Structure_Typedef* LCD_Structure_Root;
LCD_Show_Structure_Typedef* LCD_Current_Root_Node;
LCD_Show_Structure_Typedef * LCD_Selected_Structure;
int LCD_DEBUG_Count = 0;
int LCD_Show_Structure_Count = 0;
int LCD_Selected_Index = 0;


unsigned short values[20];
extern int pido;

extern int PhotoSwitchData;
extern int ls;
extern int rs;
extern int currentDirection;
extern MapNode* nextNode;
extern u8 SEN2020Datas;
extern int lfEncoderCount;
extern int rfEncoderCount;
extern int lbEncoderCount;
extern int rbEncoderCount;
extern int lfCurrentEncoderCount;
extern int rfCurrentEncoderCount;
extern int lbCurrentEncoderCount;
extern int rbCurrentEncoderCount;
extern int motorNospeedCompensate;
extern u8 respidata;
extern int pre;
extern int pulse;
extern int turnByAngle_Speed;
extern  int Nodeid1;
extern  int Nodeid2;
extern int Test_Param_Turn_Angle;
extern int TurnByPulsePremeter;
extern int KnowTreasureFlag;
extern int flashData1;
extern int aimAngle;

void LCD_Show_User_Config()
{
	LCD_Show_Structure_Typedef* Map_Start = LCD_DEBUG_Node_Add("Map_Start", 3, NULL);
	LCD_DEBUG_Function_Add("beginTravel", Travel_Begin, Map_Start);
	LCD_DEBUG_Function_Add("beginTreasure", Treasure_Begin, Map_Start);
	LCD_DEBUG_Function_Add("Travel_Test", Travel_Test, Map_Start);

	LCD_Show_Structure_Typedef* TreasureSettings = LCD_DEBUG_Node_Add("TreasureSettings", 10, NULL);
	LCD_DEBUG_Premeter_Add(TreasureIndex + 0, "Treasure1", ACCESS_LVL_READ, TreasureSettings);
	LCD_DEBUG_Premeter_Add(TreasureIndex + 1, "Treasure2", ACCESS_LVL_READ, TreasureSettings);
	LCD_DEBUG_Premeter_Add(TreasureIndex + 2, "Treasure3", ACCESS_LVL_READ, TreasureSettings);
	LCD_DEBUG_Premeter_Add(&treasurePos, "treasurePos", ACCESS_LVL_READ, TreasureSettings);
	LCD_DEBUG_Premeter_Add(&treasureIndex, "treasureIndex", ACCESS_LVL_READ, TreasureSettings);
	LCD_DEBUG_Function_Add("Reset_Value", Treasure_Reset, TreasureSettings);
	LCD_DEBUG_Function_Add("Read_Value", Treasure_Read_Treasure_Index, TreasureSettings);
	LCD_DEBUG_Function_Add("Write_test", Treasure_Write, TreasureSettings);

	LCD_Show_Structure_Typedef* TravelSettings = LCD_DEBUG_Node_Add("TravelSettings", 10, NULL);
	LCD_DEBUG_Premeter_Add(doorStatus + 0, "doorStatus0", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Premeter_Add(doorStatus + 1, "doorStatus1", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Premeter_Add(doorStatus + 2, "doorStatus2", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Premeter_Add(doorStatus + 3, "doorStatus3", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Premeter_Add(&doorIndex, "doorIndex", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Premeter_Add(&status, "status", ACCESS_LVL_READ, TravelSettings);
	LCD_DEBUG_Function_Add("Reset_Value", Travel_Reset, TravelSettings);
	LCD_DEBUG_Function_Add("Read_Value", Travel_Read_Door_Status, TravelSettings);
	LCD_DEBUG_Function_Add("Write_test", Travel_Write_Door_Status, TravelSettings);

	LCD_Show_Structure_Typedef* RouteTests = LCD_DEBUG_Node_Add("RouteTests", 5, NULL);
	LCD_DEBUG_Function_Add("MAP_goRoute_Test", MAP_goRoute_Test, RouteTests);
	LCD_DEBUG_Premeter_Add(&Nodeid1, "Nodeid1", ACCESS_LVL_READWRITEFLASH, RouteTests);
	LCD_DEBUG_Premeter_Add(&Nodeid2, "Nodeid2", ACCESS_LVL_READWRITEFLASH, RouteTests);

	LCD_Show_Structure_Typedef* PidSettings = LCD_DEBUG_Node_Add("PidSettings", 10, NULL);
	{
		LCD_Show_Structure_Typedef* SGbridgeSettings = LCD_DEBUG_Node_Add("SGbridgeSettings", 8, PidSettings);
		{
			LCD_DEBUG_Premeter_Add(&bridgeLeftSpeed, "bridgeLeftSpeed", ACCESS_LVL_READWRITEFLASH, SGbridgeSettings);
			LCD_DEBUG_Premeter_Add(&bridgeRightSpeed, "bridgeRightSpeed", ACCESS_LVL_READWRITEFLASH, SGbridgeSettings);
			LCD_DEBUG_Premeter_Add(&bridgeAngle, "bridgeAngle", ACCESS_LVL_READWRITEFLASH, SGbridgeSettings);
			LCD_DEBUG_Premeter_Add(&bridgeSpeed, "bridgeSpeed", ACCESS_LVL_READWRITEFLASH, SGbridgeSettings);
		}
		LCD_DEBUG_Premeter_Add(&Track_Kp, "Kp", ACCESS_LVL_READWRITEFLASH, PidSettings);
		LCD_DEBUG_Premeter_Add(&Track_Kd, "Kd", ACCESS_LVL_READWRITEFLASH, PidSettings);
		LCD_DEBUG_Premeter_Add(&Track_kkp, "kkp", ACCESS_LVL_READWRITEFLASH, PidSettings);
		LCD_DEBUG_Premeter_Add(&Track_kkd, "kkd", ACCESS_LVL_READWRITEFLASH, PidSettings);
		LCD_DEBUG_Premeter_Add(&straightSpeed, "Speed", ACCESS_LVL_READWRITEFLASH, PidSettings)->ChangeStep = 5;
		LCD_DEBUG_Premeter_Add(&Speed_High, "Speed_High", ACCESS_LVL_READWRITEFLASH, PidSettings)->ChangeStep = 5;
		LCD_DEBUG_Premeter_Add(&Speed_Mid, "Speed_Mid", ACCESS_LVL_READWRITEFLASH, PidSettings)->ChangeStep = 5;
		LCD_DEBUG_Premeter_Add(&Speed_Low, "Speed_Low", ACCESS_LVL_READWRITEFLASH, PidSettings)->ChangeStep = 5;
		LCD_DEBUG_Premeter_Add(&Speed_VeryHigh, "Speed_Veryhigh", ACCESS_LVL_READWRITEFLASH, PidSettings)->ChangeStep = 5;
	}


	LCD_Show_Structure_Typedef* SenserStatus = LCD_DEBUG_Node_Add("SenserStatus", 10, NULL);
	LCD_DEBUG_Premeter_Add(&IR_Front, "IR_Front", ACCESS_LVL_READ, SenserStatus)->refreshFunction = Test_getFrontIRData;
	LCD_DEBUG_Premeter_Add(&IR_button_right, "IR_button_right", ACCESS_LVL_READ, SenserStatus)->refreshFunction = getButtonIRdata;
	LCD_DEBUG_Premeter_Add(&IR_button_left, "IR_button_left", ACCESS_LVL_READ, SenserStatus);
	LCD_DEBUG_Premeter_Add(&Click_Is_Down, "Click_Is_Down", ACCESS_LVL_READ, SenserStatus)->refreshFunction = Test_getClick_TriggeredData;
	LCD_DEBUG_Premeter_Add(&LaserFrontIsOnline, "LaserFrontIsOnline", ACCESS_LVL_READ, SenserStatus)->refreshFunction = Laser_Check;
	LCD_DEBUG_Premeter_Add(&LaserLeftIsOnline, "LaserLeftIsOnline", ACCESS_LVL_READ, SenserStatus);




	LCD_Show_Structure_Typedef* CurrentStatus = LCD_DEBUG_Node_Add("CurrentStatus", 5, NULL);
	LCD_DEBUG_Premeter_Add(&currentDirection, "direction", ACCESS_LVL_READWRITE, CurrentStatus);
	LCD_DEBUG_Premeter_Add(&currentSpeed, "direction", ACCESS_LVL_READ, CurrentStatus);
	LCD_DEBUG_Premeter_Add(&currentMotorRout, "currentMotorRout", ACCESS_LVL_READ, CurrentStatus);
	LCD_DEBUG_Premeter_Add(&currentMotorLout, "currentMotorLout", ACCESS_LVL_READ, CurrentStatus);

	LCD_Show_Structure_Typedef* FlashSettings = LCD_DEBUG_Node_Add("FlashSettings", 10, NULL);
	{
		LCD_DEBUG_Function_Add("Flash_Clear_All_Data", Flash_Clear_All_Data, FlashSettings);
		LCD_DEBUG_Function_Add("Flash_ReadAll", Flash_ReadAll, FlashSettings);
		LCD_DEBUG_Function_Add("Flash_SaveAll", Flash_SaveAll, FlashSettings);
		LCD_DEBUG_Function_Add("Flash_Reset_To_Default", Flash_Reset_To_Default, FlashSettings);
		LCD_DEBUG_Function_Add("Flash_Clear_All_Data", Flash_Clear_All_Data, FlashSettings);
	}


	LCD_Show_Structure_Typedef* TestFunctions = LCD_DEBUG_Node_Add("TestFunctions", 10, NULL);
	{
		LCD_Show_Structure_Typedef* TurnTests = LCD_DEBUG_Node_Add("Turn_Tests", 10, TestFunctions);
		{

			LCD_DEBUG_Function_Add("Test_turnToOnLine", Test_turnToOnLine, TurnTests);
			LCD_DEBUG_Function_Add("Test_turnByAngle", Test_turnByAngle, TurnTests);
			LCD_DEBUG_Function_Add("Test_turnAngleByPulse", Test_turnAngleByPulse, TurnTests);
			LCD_DEBUG_Premeter_Add(&Test_Param_Turn_Angle, "Angle", ACCESS_LVL_READWRITE, TurnTests);

		}
		LCD_Show_Structure_Typedef* TrackTests = LCD_DEBUG_Node_Add("Track_Tests", 10, TestFunctions);
		{
			LCD_DEBUG_Function_Add("Test_TrackNoExceptionForLength", Test_TrackNoExceptionForLength, TrackTests);
			LCD_DEBUG_Function_Add("Test_Track", Test_Track, TrackTests);
			LCD_DEBUG_Function_Add("testGodown", testGodown, TrackTests);
			LCD_DEBUG_Function_Add("Test_goWithPulse", Test_goWithPulse, TrackTests);
			LCD_DEBUG_Premeter_Add(&Test_Param_Go_length, "aimDis", ACCESS_LVL_READWRITE, TrackTests);

			LCD_Show_Structure_Typedef* SpecialTrackTests = LCD_DEBUG_Node_Add( "SpecialTrackTests", 10, TrackTests);
			{
				LCD_DEBUG_Premeter_Add(&difSpeedLength, "testLength", ACCESS_LVL_READWRITE, SpecialTrackTests);
				LCD_DEBUG_Premeter_Add(&difLeftSpeed, "LeftSpeed", ACCESS_LVL_READWRITE, SpecialTrackTests);
				LCD_DEBUG_Premeter_Add(&difRightSpeed, "RightSpeed", ACCESS_LVL_READWRITE, SpecialTrackTests);
				LCD_DEBUG_Function_Add("goWithPulseWithDifSpeedByLbCoderTest", goWithPulseWithDifSpeedByLbCoderTest, SpecialTrackTests);
			}
		}

		LCD_Show_Structure_Typedef* ActionTests = LCD_DEBUG_Node_Add("Action_Tests", 10, TestFunctions);
		{

			LCD_DEBUG_Function_Add("Action_ShakeHead", Action_ShakeHead, ActionTests);
			LCD_DEBUG_Function_Add("Action_Handsup", Action_Handsup, ActionTests);
			LCD_DEBUG_Function_Add("Action_HandsupByOrder", Action_HandsupByOrder, ActionTests);
			LCD_DEBUG_Function_Add("Action_Handsdown", Action_Handsdown, ActionTests);
			LCD_DEBUG_Function_Add("Action_Ready", Action_Ready, ActionTests);
			LCD_DEBUG_Function_Add("Action_ArriveScene", Action_ArriveScene, ActionTests);
			LCD_DEBUG_Function_Add("Action_FindTreasure", Action_FindTreasure, ActionTests);
		}


	}


}
void LCD_Show_Init()
{
	LCD_Structure_Root = (LCD_Show_Structure_Typedef*)malloc(sizeof(LCD_Show_Structure_Typedef));
	LCD_Structure_Root->maxChildCount = 20;
	LCD_Structure_Root->children = (LCD_Show_Structure_Typedef**)malloc(sizeof(LCD_Show_Structure_Typedef*) * 20);

	LCD_Current_Root_Node = LCD_Structure_Root;

	LCD_Show_User_Config();
	LCD_Structure_Calc_Postion();
#ifdef __FLASH_DATA_ENABLED
	Flash_Init();
#endif // __FLASH_DATA_ENABLED


}
void LCD_Show_progressBar(int maxIndex, int currentIndex)
{

}

/**
* @brief  API FUNCTION  add a Led_show_structure to lcds array
* @param  dataPtr:specifies  The pointer to the data to show
* @param  fontsize:specifies  font size of data to show
*          This parameter can be 12 16 24.
* @param  top: specifies the distance from the position to the top of the screen;
*          This parameter can be from 0 to the height of lcd Normally 320
* @param  left: specifies the distance from the position to the left of the screen;
*          This parameter can be from 0 to the width of lcd Normally 240
* @param  widthChar: specifies num of chararters to be show it decides the width of the block  will be cleaned afterwards
*          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* @param  name: specifies the name of the block it can be shown
*          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* @param  showBorder: specifies whether the borader border of the block is visable
*          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* @retval None
*/

//api function 



LCD_Show_Structure_Typedef* LCD_DEBUG_Premeter_Add(
	int * premeter,
	char * name,
	int AccessLvl,
	LCD_Show_Structure_Typedef* parent
)
{

	LCD_Show_Structure_Typedef* lcd = LCD_DEBUG_Add_As_Child(premeter, name, 0, parent);
	if (!AccessLvl)
	{
		AccessLvl = ACCESS_LVL_READWRITE;
	}
	lcd->accessLvl = AccessLvl;

#ifdef __FLASH_DATA_ENABLED
	if (AccessLvl & 0x04)
	{
		Flash_Add_Data(premeter, name);
	}
#endif // __FLASH_DATA_ENABLED

	return lcd;

}



LCD_Show_Structure_Typedef* LCD_DEBUG_Function_Add(
	char * name,
	void(*leftFunction)(void),
	LCD_Show_Structure_Typedef* parent

)

{
	LCD_Show_Structure_Typedef*lcd = LCD_DEBUG_Add_As_Child(0, name, 0, parent);
	lcd->LeftFunction = leftFunction;
	return lcd;
}


LCD_Show_Structure_Typedef* LCD_DEBUG_Node_Add(
	char * name,
	int childCount,
	LCD_Show_Structure_Typedef* parent
)
{
	return LCD_DEBUG_Add_As_Child(0, name, childCount, parent);
}

LCD_Show_Structure_Typedef* LCD_DEBUG_Add_As_Child(
	int * premeter,
	char * name,
	int childCount,
	LCD_Show_Structure_Typedef * parent

)
{
	char* charDisplay = (char *)malloc(sizeof(char)*strlen(name) + 5);

	*charDisplay = 0;

	if (childCount)
	{
		strcat(charDisplay, "> ");
		strcat(charDisplay, name);
	}
	else
	{
		strcat(charDisplay, name);

		if (premeter)
		{
			strcat(charDisplay, "=  ");
		}

	}
	if (!parent)
	{
		parent = LCD_Structure_Root;
	}

	LCD_Show_Structure_Typedef* stru = _LCD_Show_Structure_Add
	(
		premeter,
		LCD_DEBUG_SHOW_CHAR_SIZE,
		LCD_DEBUG_Count++*(LCD_DEBUG_SHOW_CHAR_SIZE + 3),
		5,
		10,
		charDisplay,
		0,
		_LCD_printDec
	);

	stru->children = NULL;
	if (childCount)
	{
		stru->children = (LCD_Show_Structure_Typedef**)malloc(sizeof(LCD_Show_Structure_Typedef*)*childCount);
	}
	stru->refreshFunction = NULL;
	stru->currentChildCount = 0;
	stru->maxChildCount = childCount;
	stru->LeftFunction = 0;
	stru->RightFunction = 0;

	LCD_Add_To_Node(parent, stru);


	return stru;
}

u8 LCD_Is_Main_Root()
{
	return LCD_Current_Root_Node == LCD_Structure_Root;

}

void LCD_Add_To_Node(LCD_Show_Structure_Typedef* parent, LCD_Show_Structure_Typedef* child)
{
	if (parent == NULL)
	{
		printf("parent is NULL");
		return;
	}
	if (parent->children == NULL || parent->maxChildCount == 0)
	{
		printf("no child for %s", parent->name);
		return;
	}

	else if (parent->currentChildCount >= parent->maxChildCount)
	{
		printf("to much child in %s", parent->name);
		return;

	}

	else
	{
		parent->children[parent->currentChildCount++] = child;
		child->parent = parent;

	}
}


LCD_Show_Structure_Typedef * _LCD_Show_Structure_Add(
	int  *dataPtr,
	u8 fontsize,
	u16 top,
	u16 left,
	u16 widthChar,
	char* name,
	u8 showBorder,
	void(*showFunction)(void *, LCD_Show_Structure_Typedef *)

)
{
	LCD_Show_Structure_Typedef* new_LCD_Structure = (LCD_Show_Structure_Typedef*)malloc(sizeof(LCD_Show_Structure_Typedef));
	if (!new_LCD_Structure)
	{
		LCD_printf("no memory for more lcds");
		return NULL;
	}
	new_LCD_Structure->name = name;
	if (name != NULL)
	{
		new_LCD_Structure->_namelength = strlen(new_LCD_Structure->name);
	}
	else
	{
		new_LCD_Structure->_namelength = 0;
	}
	new_LCD_Structure->widthChar = widthChar + new_LCD_Structure->_namelength;

	new_LCD_Structure->dataPtr = dataPtr;
	new_LCD_Structure->fontSize = fontsize;
	new_LCD_Structure->_fontWidth = fontsize / 2;
	new_LCD_Structure->top = top;

	new_LCD_Structure->showFunction = showFunction;
	new_LCD_Structure->left = left;
	new_LCD_Structure->showBorder = showBorder;
	new_LCD_Structure->_width = new_LCD_Structure->widthChar*new_LCD_Structure->_fontWidth;
	LCD_Show_Structures[LCD_Show_Structure_Count] = new_LCD_Structure;

	LCD_Show_Structure_Count++;
	return new_LCD_Structure;
}

void LCD_Show()
{
	LCD_Show_Tree(LCD_Current_Root_Node);
}

void LCD_Show_Tree(LCD_Show_Structure_Typedef* lcd)
{
	int index = 0;
	LCD_Selected_Structure = LCD_Get_Current_Selected_Node();
	if (lcd != LCD_Structure_Root)
	{
		_LCD_Structure_Show(lcd);
	}
	for (int i = 0; i < lcd->currentChildCount; i++)
	{
		_LCD_Structure_Show(lcd->children[i]);
	}
}

void LCD_NextNode(LCD_Show_Structure_Typedef * currentNode)
{
	LCD_Selected_Index = 0;
	LCD_Current_Root_Node = currentNode;
	LCD_Show_Clear();
	LCD_Structure_Calc_Postion();
	LCD_Clear(0xffff);
}

void LCD_GoBack()
{
	if (LCD_Current_Root_Node->parent)
	{
		LCD_Selected_Index = 0;
		LCD_Current_Root_Node = LCD_Current_Root_Node->parent;
		LCD_Structure_Calc_Postion();
		LCD_Show_Clear();
		LCD_Clear(0xffff);
	}
}

void LCD_Show_Clear()
{
	LCD_Show_Structure_Typedef * lcd;

	for (int i = 0; i < LCD_Current_Root_Node->currentChildCount; i++)
	{
		lcd = LCD_Current_Root_Node->children[i];
		lcd->showBorder = false;

		_LCD_Show_Clear_Area(lcd);
		_LCD_Clear_Border(lcd);
	}

}

LCD_Show_Structure_Typedef* LCD_Get_Current_Selected_Node()
{
	if (LCD_Is_Main_Root())
	{
		return 	LCD_Current_Root_Node->children[LCD_Selected_Index];
	}
	else
	{
		if (LCD_Selected_Index == 0)
		{
			return LCD_Current_Root_Node;
		}
		else
		{
			return LCD_Current_Root_Node->children[LCD_Selected_Index - 1];
		}
	}
}

void _LCD_Structure_Show(LCD_Show_Structure_Typedef* lcd)
{
	lcd->_currentOffset = 0;
	_LCD_Show_Clear_Area(lcd);

	if (lcd == LCD_Selected_Structure)
	{
		_LCD_Show_Draw_Border(lcd);
	}
	else
	{
		_LCD_Clear_Border(lcd);
	}
	int charIndex = 0;
	if (lcd->refreshFunction)
	{
		lcd->refreshFunction();

	}
	if (lcd->name != NULL)
	{
		char * str = lcd->name;
		while (*str)
		{
			LCD_Show_PutCh(*str++, charIndex++, lcd);
		}
	}
	if (lcd->dataPtr != NULL)
	{
		int num = *((int *)(lcd->dataPtr));
		if (num < 0)
		{
			num = -num;
			LCD_Show_PutCh('-', charIndex++, lcd);
		}
		char str[32] = "";
		int len = 0;
		do	str[len++] = num % 10 + 48; while (num /= 10);
		while (len--)	LCD_Show_PutCh(str[len], charIndex++, lcd);
	}
}

void LCD_Show_PutCh(char ch, int charIndex, LCD_Show_Structure_Typedef* currentLcd)
{
	int x = currentLcd->left + charIndex*currentLcd->_fontWidth;
	int y = currentLcd->top;

	LCD_DisplayChar(x, y, ch, currentLcd->fontSize);
}

void LCD_Structure_Calc_Postion()
{
	int pos = 0;

	if (!LCD_Is_Main_Root())
	{
		LCD_Current_Root_Node->top = pos;
		pos++;
	}

	for (int i = 0; i < LCD_Current_Root_Node->currentChildCount; i++)
	{
		LCD_Show_Structure_Typedef* lcd = LCD_Current_Root_Node->children[i];
		lcd->top = pos*(LCD_DEBUG_SHOW_CHAR_SIZE + 3);
		pos++;
	}

}

void _LCD_Show_Clear_Area(LCD_Show_Structure_Typedef * lcd)
{
	LCD_Fill_onecolor(
		LIMIT(lcd->left, 0, WIDTH),
		LIMIT(lcd->top, 0, HEIGHT),
		LIMIT(lcd->left + lcd->_width, 0, WIDTH),
		LIMIT(lcd->top + lcd->fontSize, 0, HEIGHT),
		0xffff);
}

void _LCD_Show_Draw_Border(LCD_Show_Structure_Typedef * lcd)
{
	LCD_Draw_Rectangle(
		LIMIT(lcd->left - 1, 0, WIDTH),
		LIMIT(lcd->top - 1, 0, HEIGHT),
		LIMIT(lcd->left + lcd->_width + 1, 0, WIDTH),
		LIMIT(lcd->top + lcd->fontSize + 1, 0, HEIGHT)
	);
}

void _LCD_Clear_Border(LCD_Show_Structure_Typedef * lcd)
{
	u16 brushBefore = BRUSH_COLOR;
	BRUSH_COLOR = BACK_COLOR;

	LCD_Draw_Rectangle(
		LIMIT(lcd->left - 1, 0, WIDTH),
		LIMIT(lcd->top - 1, 0, HEIGHT),
		LIMIT(lcd->left + lcd->_width + 1, 0, WIDTH),
		LIMIT(lcd->top + lcd->fontSize + 1, 0, HEIGHT)
	);
	BRUSH_COLOR = brushBefore;
}

void _LCD_data_Increase(LCD_Show_Structure_Typedef * lcd)
{
	if (!(lcd->accessLvl & 0x02))
	{
		return;
	}
	if (!lcd->ChangeStep)
	{
		lcd->ChangeStep = 1;
	}
	(*(lcd->dataPtr)) += lcd->ChangeStep;

}
void _LCD_data_Decrease(LCD_Show_Structure_Typedef * lcd)
{
	if (!(lcd->accessLvl & 0x02))
	{
		return;
	}
	if (!lcd->ChangeStep)
	{
		lcd->ChangeStep = 1;
	}
	(*(lcd->dataPtr)) -= lcd->ChangeStep;
}
void _LCD_DEBUG_KEY_DOWN()
{

	int downMax = LCD_Current_Root_Node->currentChildCount;

	if (!LCD_Is_Main_Root())
	{
		downMax++;
	}
	if (LCD_Selected_Index + 1 < downMax)
	{
		LCD_Selected_Index++;
	}
}
void _LCD_DEBUG_KEY_UP()
{

	if (LCD_Selected_Index - 1 >= 0)
	{
		LCD_Selected_Index--;
	}

}
void _LCD_DEBUG_KEY_LEFT()
{

	LCD_Selected_Structure = LCD_Get_Current_Selected_Node();

	if (LCD_Selected_Structure->children)
	{
		LCD_NextNode(LCD_Selected_Structure);
	}
	else if (LCD_Selected_Structure->LeftFunction)
	{
		LCD_Selected_Structure->LeftFunction();
	}
	else
	{
		_LCD_data_Decrease(LCD_Selected_Structure);
	}
}
void _LCD_DEBUG_KEY_RIGHT()
{

	LCD_Selected_Structure = LCD_Get_Current_Selected_Node();

	if (LCD_Selected_Structure == LCD_Current_Root_Node)
	{
		LCD_GoBack();
	}
	else if (LCD_Selected_Structure->RightFunction)
	{
		LCD_Selected_Structure->RightFunction();
	}
	else
	{
		_LCD_data_Increase(LCD_Selected_Structure);
	}
}
