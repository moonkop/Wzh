#include "main.h"



extern void Read_TreasureIndex();
extern void Read_Door_Status();

void Flash_Reset()
{
	FLASH_Clear(TREASURE_FIRST_ADDRESS);
	FLASH_Clear(TRAVEL_FIRST_ADDRESS);
	Treasure_Read_Treasure_Index();
	Travel_Read_Door_Status();

}


u8 Flash_Write_One_Data(int data, u32 address,int offset)
{
	int value = FLASH_READ_ONEDATA(offset,address);
	if (value !=0xffffffff)
	{
		LCD_printf("warning Flash%d not empty =%d\n", address,value);
	} 
	FLASH_WRITE_ONEDATA(data, offset, address);
	int readValue = FLASH_READ_ONEDATA(offset, address);

	if (readValue!=data)
	{
		LCD_printf("error Flash write Failed address=%d , offset=%d ,data= %d, readValue=%d\n", address, offset, data, readValue);
		return 0;
	}
	else
	{
		LCD_printf("flash Write Succeed\n");
		return 1;
	}
}