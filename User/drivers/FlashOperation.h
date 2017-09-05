#ifndef __FLASHOPERATION_H
#define __FLASHOPERATION_H

#include "../devices/bsp_flash.h"



void Flash_Reset();

u8 Flash_Write_One_Data(int data, u32 address, int offset);

#endif