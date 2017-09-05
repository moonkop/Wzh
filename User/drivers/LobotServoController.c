#include "LobotServoController.h"

#define GET_LOW_BYTE(A) (uint8_t)((A))
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))


uint8_t  numOfActinGroupRunning; 
uint16_t actionGroupRunTimes; 
u8 isRunning; 
uint16_t batteryVoltage;

void LobotServoControllerInit(void)
{
	numOfActinGroupRunning = 0xFF;
	actionGroupRunTimes = 0;
	isRunning = 0;
	batteryVoltage = 0;
}


void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time)
{
	uint8_t buf[11];
	if (servoID > 31 || !(Time > 0)) { 
		return;
	}
	buf[0] = FRAME_HEADER;                   
	buf[1] = FRAME_HEADER;
	buf[2] = 8;                              
	buf[3] = CMD_SERVO_MOVE;                 
	buf[4] = 1;                              
	buf[5] = GET_LOW_BYTE(Time);            
	buf[6] = GET_HIGH_BYTE(Time);            
	buf[7] = servoID;                        
	buf[8] = GET_LOW_BYTE(Position);         
	buf[9] = GET_HIGH_BYTE(Position);       

	Usart3_Send(buf, 10);
}

/*********************************************************************************
 * Function:  moveServos
 * Description: ????????
 * Parameters:   servos[]:??????,Num:????,Time:????
                    0 < Num <= 32,Time > 0
 * Return:       ???
 * Others:
 **********************************************************************************/
void moveServos(struct LobotServo servos[], uint8_t Num, uint16_t Time)
{
	uint8_t buf[103];    
	if (Num < 1 || Num > 32 || !(Time > 0)) {
		return; 
	}
	buf[0] = FRAME_HEADER;  
	buf[1] = FRAME_HEADER;
	buf[2] = Num * 3 + 5;     
	buf[3] = CMD_SERVO_MOVE;  
	buf[4] = Num;             
	buf[5] = GET_LOW_BYTE(Time); 
	buf[6] = GET_HIGH_BYTE(Time); 
	uint8_t index = 7;
	for (uint8_t i = 0; i < Num; i++) { 
		buf[index++] = servos[i].ID; 
		buf[index++] = GET_LOW_BYTE(servos[i].Position); 
		buf[index++] = GET_HIGH_BYTE(servos[i].Position);
	}
	Usart3_Send(buf, buf[2] + 2); 
}


/*********************************************************************************
 * Function:  runActionGroup
 * Description: ???????
 * Parameters:   NumOfAction:?????, Times:????
 * Return:       ???
 * Others:       Times = 0 ?????
 **********************************************************************************/
void runActionGroup(uint8_t numOfAction, uint16_t Times)
{
	uint8_t buf[7];
	buf[0] = FRAME_HEADER;  
	buf[1] = FRAME_HEADER;
	buf[2] = 5;      
	buf[3] = CMD_ACTION_GROUP_RUN; 
	buf[4] = numOfAction;     
	buf[5] = GET_LOW_BYTE(Times); 
	buf[6] = GET_HIGH_BYTE(Times); 
	Usart3_Send(buf, 7);
}

/*********************************************************************************
 * Function:  stopActiongGroup
 * Description: ???????
 * Parameters:   Speed: ????
 * Return:       ???
 * Others:
 **********************************************************************************/
void stopActiongGroup(void)
{
	uint8_t buf[4];
	buf[0] = FRAME_HEADER;     
	buf[1] = FRAME_HEADER;
	buf[2] = 2;                
	buf[3] = CMD_ACTION_GROUP_STOP; 

	Usart3_Send(buf, 4);    
}

void setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed)
{
	uint8_t buf[7];
	buf[0] = FRAME_HEADER;     
	buf[1] = FRAME_HEADER;
	buf[2] = 5;                
	buf[3] = CMD_ACTION_GROUP_SPEED; 
	buf[4] = numOfAction;     
	buf[5] = GET_LOW_BYTE(Speed); 
	buf[6] = GET_HIGH_BYTE(Speed);

	Usart3_Send(buf, 7);     
}



void setAllActionGroupSpeed(uint16_t Speed)
{
	setActionGroupSpeed(0xFF, Speed); 
}



