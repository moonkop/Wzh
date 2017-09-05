#include "WS2811.h"

/**********************说明*****************************


如果多灯珠，需要用到void WS_SetAll(void)和Wsdat[]等等
*******************************************************/

uint16_t PixelBuffer[328] = { 0 };
uint16_t PixelPointer = 0;

unsigned long Color_red = 0x00ff0000;
unsigned long Color_green = 0x0000ff00;
unsigned long Color_blue = 0x000000ff;
unsigned long Color_pink = 0x00ffb7dd;
unsigned long Color_purple = 0x009900ff;
unsigned long Color_yellow = 0x00ffff00;
unsigned long Color_cyan = 0x0000ffff;
unsigned long Color_white = 0x00ffffff;

unsigned long WsDat[nWs] = { 0xFF0000,0xFF0000,0xFF0000,
						  0xFF0000,0xFF0000,0xFF0000,
													0xFF0000,0xFF0000,0xFF0000,
													0xFF0000,0xFF0000,0xFF0000 };

//存放颜色以及优先级
unsigned long Color_Data[50][2] = { 0 };
int color_cnt = 0;
//颜色  、权限								
void SetColor_Priority(int color, int priority)
{
	Color_Data[color_cnt][0] = color;
	Color_Data[color_cnt][1] = priority;
	color_cnt++;
}
void WS2811_Breath()
{
	const static u8 brightness = 255;
	static unsigned long breath_color = brightness << 16;
	uint8_t Red, Green, Blue;  // 三原色
	// 绿 红 蓝 三原色分解
	Red = breath_color >> 16;
	Green = breath_color >> 8;
	Blue = breath_color;

	if (Blue == 0x00)
	{
		if (Green < brightness)
		{
			Green++;
			Red--;
		}
	}
	if (Red == 0x00)
	{
		if (Blue < brightness)
		{
			Blue++;
			Green--;
		}
	}
	if (Green == 0x00)
	{
		if (Red < brightness)
		{
			Red++;
			Blue--;
		}
	}
	breath_color = (Red << 16) + (Green << 8) + Blue;

	LED_SPI_Update(&breath_color, 1);
}

void LED_SPI_LowLevel_Init(void)
{
	uint16_t i = 0;

	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;
	DMA_InitTypeDef   DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);//c3 spi2

	//RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);//复位SPI1? ?? ???
	//RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);//停止复位SPI1? ??

	DMA_DeInit(DMA1_Stream4);

	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI2->DR));
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)PixelBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;

	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	//DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE); //开 DMA2_Stream0 中断 
	//DMA_Cmd(DMA1_Stream4, ENABLE); //开DMA2_Stream0 

	DMA_Init(DMA1_Stream4, &DMA_InitStructure); /* DMA1 CH3 = MEM -> DR */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	SPI_I2S_DeInit(SPI2);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//单向发送
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//主机
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; /* 48MHz / 8 = 6MHz */
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//高位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

	SPI_Cmd(SPI2, ENABLE);

	for (i = 0; i < 328; i++)
	{
		PixelBuffer[i] = 0xAAAA;
	}

	PixelPointer = 0;
}

void WS_SetAll()
{
	unsigned char j;
	unsigned long temp;

	temp = WsDat[0];
	for (j = 0; j < 11; j++)
	{
		WsDat[j] = WsDat[j + 1];
	}
	WsDat[11] = temp;
}

void WS2811_Update()
{
	int max_priority = 0;
	for (int i = 0; i < color_cnt; i++)
	{
		if (Color_Data[i][1] < Color_Data[max_priority][1])
			max_priority = i;
	}
	LED_SPI_Update(&Color_Data[max_priority][0], 1);
	color_cnt = 0;
}

void LED_SPI_Update(unsigned long buffer[], uint32_t length)
{
	uint8_t i = 0;
	uint8_t m = 0;
	if (DMA_GetCurrDataCounter(DMA1_Stream4) == 0)
	{

		for (i = 0; i < length; i++)
		{
			LED_SPI_SendPixel(buffer[i]);
		}

		if (length < 12)
		{
			for (i = 12 - length; i < length; i++)
			{
				for (m = 0; m < 3; m++)
				{
					LED_SPI_SendBits(0x00);
				}
			}
		}

		/* (20+1) * 2.5 = 51.5 ~ 52.5us */
		for (i = 0; i < 20; i++)
		{
			LED_SPI_WriteByte(0x00);
		}

		PixelPointer = 0;

		DMA_Cmd(DMA1_Stream4, DISABLE);
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA_SetCurrDataCounter(DMA1_Stream4, 24 * length + 20);
		DMA_Cmd(DMA1_Stream4, ENABLE);
	}
}
unsigned long WS2811_Color;

void setPixelColor(unsigned long buffer)
{
	//LED_SPI_Update(&buffer, 1);
	WS2811_Color = buffer;

}

void WS2811_Update_Color()
{
	LED_SPI_Update(&WS2811_Color, 1);
}

void LED_SPI_SendBits(uint8_t bits)
{
	int zero = 0x7000;  //111000000000000
	int one = 0xFF00;  //0x7f00和oxff00一样效果
	int i = 0x00;

	for (i = 0x80; i >= 0x01; i >>= 1)
	{
		LED_SPI_WriteByte((bits & i) ? one : zero);
	}
}

void LED_SPI_WriteByte(uint16_t Data)
{
	/* Wait until the transmit buffer is empty */
	/*
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
	}
	*/

	PixelBuffer[PixelPointer] = Data;
	PixelPointer++;

	/* Send the byte */
	/* SPI_I2S_SendData16(SPI1, Data); */
}

void LED_SPI_SendPixel(uint32_t color)
{
	/*
	 r7,r6,r5,r4,r3,r2,r1,r0,g7,g6,g5,g4,g3,g2,g1,g0,b7,b6,b5,b4,b3,b2,b1,b0
	 \_____________________________________________________________________/
							   |      _________________...
							   |     /   __________________...
							   |    /   /   ___________________...
							   |   /   /   /
							  RGB,RGB,RGB,RGB,...,STOP
	*/

	/*
		BUG Fix : Actual is GRB,datasheet is something wrong.
	*/
	uint8_t Red, Green, Blue;  // 三原色
	  // 绿 红 蓝 三原色分解
	Red = color >> 16;
	Green = color >> 8;
	Blue = color;

	LED_SPI_SendBits(Green);
	LED_SPI_SendBits(Red);
	LED_SPI_SendBits(Blue);
}
