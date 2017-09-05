#ifndef _LOBOTSERVOCONTROLLER_H
#define _LOBOTSERVOCONTROLLER_H

#include "stm32f4xx.h"
#include "USART.h"


#define FRAME_HEADER            0x55
#define CMD_SERVO_MOVE          0x03
#define CMD_ACTION_GROUP_RUN    0x06
#define CMD_ACTION_GROUP_STOP   0x07
#define CMD_ACTION_GROUP_SPEED  0x0B
#define CMD_GET_BATTERY_VOLTAGE 0x0F


#define BATTERY_VOLTAGE       0x0F
#define ACTION_GROUP_RUNNING  0x06
#define ACTION_GROUP_STOPPED  0x07
#define ACTION_GROUP_COMPLETE 0x08

extern uint8_t  numOfActinGroupRunning;
extern uint16_t actionGroupRunTimes;
extern u8 isRunning; 
extern uint16_t batteryVoltage; 

struct LobotServo {  
  uint8_t  ID;       
  uint16_t Position; 
};

void LobotServoControllerInit(void);

void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time);
void moveServos(struct LobotServo servos[], uint8_t Num, uint16_t Time);
void runActionGroup(uint8_t NumOfAction, uint16_t Times);
void stopActiongGroup(void);
void setActionGroupSpeed(uint8_t NumOfAction, uint16_t Speed);
void setAllActionGroupSpeed(uint16_t Speed);

#endif
