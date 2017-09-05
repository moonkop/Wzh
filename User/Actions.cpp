#include "Actions.h"
#include "common.h"
void Action_Ready()
{
	runActionGroup(0, 1);
}
void Action_Handsup()
{
	runActionGroup(1, 1);
}
void Action_HandsupByOrder()
{
	runActionGroup(4, 1);
}
void Action_Handsdown()
{
	runActionGroup(2, 1);
}
void Action_FindTreasure()
{
	Action_Handsup();
	delay_ms(500);
	Action_Handsdown();
	delay_ms(200);
}
void Action_ArriveScene()
{
	Action_HandsupByOrder();
	delay_ms(700);
}

void Action_ShakeHead()
{
	runActionGroup(3, 1);
//	delay_ms(3000);
	runActionGroup(2, 1);
}