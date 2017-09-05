#include "Flash.h"
#include "stdlib.h"
#include "string.h"
#include "../drivers/FlashOperation.h"
#include "../devices/bsp_flash.h"
int Flash_Data_Strcture_Count;
int currentOffset;
Flash_Data_Typedef *Flash_Data_Strctures[100];
void Flash_User_Config()
{

}

void Flash_Init()
{
	Flash_User_Config();
	Flash_ReadAll();

}
void Flash_ReadAll()
{
	Flash_Data_Typedef * flashdata;
	for (int i = 0; i < Flash_Data_Strcture_Count; i++)
	{
		flashdata = Flash_Data_Strctures[i];
		*(flashdata->valuePtr) = FLASH_READ_ONEDATA(0, flashdata->_address);
	}
}

void Flash_SaveAll()
{
	Flash_Data_Typedef * flashdata;
	for (int i = 0; i < Flash_Data_Strcture_Count; i++)
	{
		flashdata = Flash_Data_Strctures[i];
		Flash_Write_Structure(flashdata);
	}
}
void Flash_Clear_All_Data()
{
	FLASH_Clear(FLASH_DATA_FIRST_ADDRESS);
}
bool Flash_Write_Structure(Flash_Data_Typedef * flashdata)
{
	return Flash_Write_One_Data(*(flashdata->valuePtr), flashdata->_address, 0);
}
void Flash_Reset_To_Default()
{
	Flash_Data_Typedef * flashdata;
	for (int i = 0; i < Flash_Data_Strcture_Count; i++)
	{
		flashdata = Flash_Data_Strctures[i];
		*(flashdata->valuePtr)= flashdata->defaultValue;
	}
}


void Flash_Add_Data(int* dataPtr, char* name)
{
	_Flash_Add_Data(dataPtr, name, currentOffset);
	currentOffset += 4;

}


void _Flash_Add_Data(int* dataPtr, char* name,int offset)
{
	Flash_Data_Typedef* new_Flash_Data_Structure = (Flash_Data_Typedef*)malloc(sizeof(Flash_Data_Typedef));	
	new_Flash_Data_Structure->valuePtr = dataPtr;
	new_Flash_Data_Structure->defaultValue = *dataPtr;
	new_Flash_Data_Structure->offset = offset;
	
	if (name)
	{
		new_Flash_Data_Structure->name = (char*)malloc(sizeof(char)*strlen(name)+1);
	}
	else
	{
		name = NULL;
	}
	new_Flash_Data_Structure->_address = FLASH_DATA_FIRST_ADDRESS + offset;
	Flash_Data_Strctures[Flash_Data_Strcture_Count++] = new_Flash_Data_Structure;

}
