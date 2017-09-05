
#include "stm32f4xx.h"
#include "drivers\LobotServoController.h"
#ifndef __ACTIONS_H
#define __ACTIONS_H
void Action_Ready();
void Action_Handsup();
void Action_Handsdown();
void Action_HandsupByOrder();
void Action_FindTreasure();
void Action_ArriveScene();
void Action_ShakeHead();

#endif // !__ACTIONS_H
