#ifndef __EXCEPTIONFUNCTION_H
#define __EXCEPTIONFUNCTION_H

#include "track.h"
#include "sen2020.h"
#include "buttonIR.h"
#include "LCD_driver\LCD_print.h"
#include "PhotoSwitch.h"
#include "KEY.h"	

bool _ExceptionFunction_MutiToOneLine();

bool _ExceptionFunction_ToMutiline();

bool _ExceptionFunction_vertial();

bool _ExceptionFunction_IRClose();

bool _ExceptionFunction_NoLine();

bool _ExceptionFunction_OneLine();

bool _ExceptionFunction_ArriveDoor();

bool _ExceptionFunction_Bagua();

bool _ExceptionFunction_SideClose();

bool _ExceptionFunction_Click();



#endif


