#include "mpu_user_api.h"
#include "eMPL\mpu_user_api.h"
#include "stm32_iic.h"
#include "..\MAP\map.h"
#include "MPU6050.h"
#include "main.h"
#include "preProcesser.h"
extern int motorPitchOffset;
void MPU_test()
{
	Update_attitude_Angle();
	LCD_printf("P:");
	LCD_printf("%f ", Pitch);
	LCD_printf("R:");
	LCD_printf("%f ", Roll);
	LCD_printf("Y:");
	LCD_printf("%f ", Yaw);
	Update_Magnetometer();
	LCD_printf("M:%d \n", Direction);

}
void MPU_Init()
{
	_Mpu_Init(1);
	LCD_printf("MPU Init succeed getting Status....\n");

	MPU_Update_Angle();

	LCD_printf("Roll=%f,Yaw=%f,pitch=%f\n", Roll, Yaw, Pitch);
	MPU_Update_Magenet();
	LCD_printf("M:%d \n\n", Direction);
}
void MPU_Update_Angle()
{
	Update_attitude_Angle();

}
void MPU_Update_Magenet()
{
	Update_Magnetometer();

}

bool MotorPitchcompensationOnFlag = 0;
int getMotorPitchOffset()
{
	if (MotorPitchcompensationOnFlag)
	{
		return	motorPitchOffset = (int)(Pitch*1.5);
	}
	else
	{
		return	motorPitchOffset = 0;

	}
}
