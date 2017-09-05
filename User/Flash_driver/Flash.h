#ifndef __FLASH_H
#define	__FLASH_H
#include "stm32f4xx.h"
#include "bsp_flash.h"
#define FLASH_DATA_FIRST_ADDRESS 0x08040000
#define __FLASH_DATA_ENABLED
typedef struct _Flash_Data_Typedef
{
	int defaultValue;
	int _address;
	int* valuePtr;
	int offset;
	char * name;
}Flash_Data_Typedef;




void Flash_User_Config();
void Flash_Init();

void Flash_ReadAll();

void Flash_SaveAll();

void Flash_Clear_All_Data();

bool Flash_Write_Structure(Flash_Data_Typedef * flashdata);

void Flash_Reset_To_Default();

void Flash_Add_Data(int * dataPtr, char * name);

void _Flash_Add_Data(int * dataPtr, char * name, int offset);



#endif