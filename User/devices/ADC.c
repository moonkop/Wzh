#include "stm32f4xx.h"
#include "ADC.h"
#include "../preProcesser.h"
void ADC3_init()
{
	GPIO_InitTypeDef g;
	g.GPIO_Mode = GPIO_Mode_AN;
	g.GPIO_PuPd = GPIO_PuPd_NOPULL;
	g.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_3;
	GPIO_Init(GPIOF,&g);



	ADC_InitTypeDef a;
	a.ADC_Resolution = ADC_Resolution_12b;
	a.ADC_ScanConvMode = DISABLE;
	a.ADC_ContinuousConvMode = DISABLE;
	a.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	a.ADC_DataAlign = ADC_DataAlign_Right;
	a.ADC_NbrOfConversion = 1;
	ADC_Init(ADC3, &a);
	ADC_Cmd(ADC3, ENABLE);

}



void  ADC1_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;


														 //先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PA5 通道6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);	//复位结束	 


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化

	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}



/****************************************************************************
* 名    称: u16 Get_Adc(u8 ch)
* 功    能：获得ADC值
* 入口参数：ch: 通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
* 返回参数：12位ADC有效值
* 说    明：
****************************************************************************/
u16 Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    

	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 GetAdc3(u8 ch)
{
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	
	while (!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));//等待转换结束

	return ADC_GetConversionValue(ADC3);	//返回最近一次ADC1规则组的转换结果
}

/****************************************************************************
* 名    称: u16 Get_Adc_Average(u8 ch,u8 times)
* 功    能：获取通道ch的转换值，取times次,然后平均
* 入口参数：ch: 通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
*           times:获取次数
* 返回参数：通道ch的times次转换结果平均值
* 说    明：
****************************************************************************/
u16 Get_Adc_Average(u8 ch, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for (t = 0; t<times; t++)
	{
		temp_val += Get_Adc(ch);
		//delay_ms(5);
	}
	return temp_val / times;
}










