//#include "main.h"
#include "buttonIR.h"
#include "myMath.h"
#include "../preProcesser.h"
#include "adc.h"
#include "../LCD_driver/LCD_print.h"
int IR_button_left = 0;
int IR_button_right = 0;
int IR_Front = 0;



void getButtonIRdata()

{
	 IR_button_left = Get_Adc(ADC_Channel_5);
	 IR_button_right = GetAdc3(ADC_Channel_9);
}

void Test_getFrontIRData()
{
	getFrontIRData();
}

int getFrontIRData()
{
	 IR_Front = GetAdc3(ADC_Channel_14);

	 return IR_Front;
}

int getFrontIRDataAfterFitter()
{
	return Moving_Median_int(getFrontIRData(), 1);

}