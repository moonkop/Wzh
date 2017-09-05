#ifndef  __BUTTON_IR
#define	__BUTTON_IR
#include "stm32f4xx.h"
extern int IR_button_left ;
extern int IR_button_right ;
extern int IR_Front;

void getButtonIRdata();

int getFrontIRData();
void Test_getFrontIRData();
int getFrontIRDataAfterFitter();

#endif // !__BUTTON_IR
