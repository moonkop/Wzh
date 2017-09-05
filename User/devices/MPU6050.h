#ifndef __MPU_6050_H
#define __MPU_6050_H




void MPU_test();

void MPU_Init();

void MPU_Update_Angle();

void MPU_Update_Magenet();

int getMotorPitchOffset();


extern float Roll;
extern float Yaw;
extern float Pitch;
extern bool MotorPitchcompensationOnFlag;
#endif
