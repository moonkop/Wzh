#include "bsp_flash.h"     
  
FLASH_FLAG FLASH_STATUS;  
u32 value;
static u32 count = 0;  
int FlashDataCount = 0;

/******************************************************
��������: uint32_t GetSector(uint32_t Address)
��    ��:�жϵ�ַ���ڵ�Sector
��    ��:uint32_t Address :�洢�ռ��׵�ַ
��    ��:uint32_t :Sector���
******************************************************/

uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

  return sector;
}

/**---------------------------------------------------------------------------------
* @brief   FLASHд��ز����ٵĲ���
* @param  ����������ʼ��ַ
* @retval ��������ִ�����
--------------------------------------------------------------------------------*/

unsigned char FLASH_Clear(u32 add)
{
	/*Enables or disables the Internal High Speed oscillator (HSI).*/
	RCC_HSICmd(ENABLE);
	/*��FLASH�ɲ���������*/
	FLASH_Unlock();
	/*��flash��־λȫ��*/
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
		FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	FLASH_EraseSector(GetSector(add), VoltageRange_3);

	/* Locks the FLASH Program Erase Controller.*/
	FLASH_Lock();
	RCC_HSICmd(DISABLE);
	FLASH_STATUS = FLASH_WRITE_OK;
	return FLASH_STATUS;
}

/**--------------------------------------------------------------------------------- 
  * @brief   FLASHд��ز����ٵĲ��� 
  * @param  ����������ʼ��ַ
  * @retval ��������ִ�����
  --------------------------------------------------------------------------------*/  
  
unsigned char FLASH_WRITE(int* memory_data,int dataLength)
{     
    static int t;  
    count = 0;
    /*Enables or disables the Internal High Speed oscillator (HSI).*/  
    RCC_HSICmd(ENABLE);
    /*��FLASH�ɲ���������*/
    FLASH_Unlock();
    /*��flash��־λȫ��*/
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
    FLASH_EraseSector(GetSector(FIRST_ADDRESS),VoltageRange_3);  
	t = dataLength;
//    while(count <= t)  
//    {  
//        /*flash Ϊһ���ֽڴ洢,32λ���ݱ����ַ��4*/  
//        FLASH_ProgramWord((FIRST_ADDRESS +count*4),*(memory_data+count));   
//        count++;  
//        if(count > t)  
//        {  
//            FLASH_STATUS = FLASH_WRITE_NO;  
//            return FLASH_STATUS;  
//        }  
//    }  
    /* Locks the FLASH Program Erase Controller.*/  
    FLASH_Lock();   
    RCC_HSICmd(DISABLE);  
    FLASH_STATUS = FLASH_WRITE_OK;  
    return FLASH_STATUS;  
}  

/**---------------------------------------------------------------------------------
* @brief   FLASHд��ز����ٵĲ���
* @param  ����������ʼ��ַ
* @retval ��������ִ�����
--------------------------------------------------------------------------------*/

unsigned char FLASH_WRITE_ONEDATA(int memory_data, int offset,u32 add)
{
	/*Enables or disables the Internal High Speed oscillator (HSI).*/
	RCC_HSICmd(ENABLE);
	/*��FLASH�ɲ���������*/
	FLASH_Unlock();
	/*��flash��־λȫ��*/
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
		FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	/*flash Ϊһ���ֽڴ洢,32λ���ݱ����ַ��4*/
	FLASH_ProgramWord((add + offset * 4), memory_data);
	/* Locks the FLASH Program Erase Controller.*/
	FLASH_Lock();
	RCC_HSICmd(DISABLE);
	FLASH_STATUS = FLASH_WRITE_OK;
	return FLASH_STATUS;
}

  
/**--------------------------------------------------------------------------------- 
  * @brief   FLASH��������
  * @param  memory_data:�����ŵ�ַ,n �������
  * @retval ��������ִ�����
  --------------------------------------------------------------------------------*/

unsigned char FLASH_READ(int * memory_data,unsigned short int n)
{     
    count = 0;  
    while(count < n)  
    {  
      *(memory_data+count) = *(u32 *)(FIRST_ADDRESS + count*4);  
        //printf("\r %d \r",*(memory_data+count));   //??  
        count++;  
        if(count > n)  
        {  
            FLASH_STATUS = FLASH_READ_NO;     
            return FLASH_STATUS;  
        }  
    }  
    //FLASH_ErasePage(0x8002000);  
    FLASH_STATUS = FLASH_READ_OK;  
    return FLASH_STATUS;  
}  

/**---------------------------------------------------------------------------------
* @brief   FLASH����һλ����
* @param ���ݵ�λ��
* @retval ����������
--------------------------------------------------------------------------------*/

unsigned int FLASH_READ_ONEDATA(u8 offset,u32 add)
{
	value = *(u32 *)(add + offset * 4);
	return value;
}
  
/*********************************************END OF FILE**********************/ 