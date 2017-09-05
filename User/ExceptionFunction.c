#include "ExceptionFunction.h"

bool _ExceptionFunction_MutiToOneLine_MutiFlag = 0;
bool _ExceptionFunction_MutiToOneLine()
{
	if (_ExceptionFunction_MutiToOneLine_MutiFlag == 0)
	{
		if (linecountAfterFitter() == 1)
		{
			return false;
		}
		else
		{
			_ExceptionFunction_MutiToOneLine_MutiFlag = 1;
			return false;
		}
	}
	else
	{
		if (linecountAfterFitter() == 1)
		{
			_ExceptionFunction_MutiToOneLine_MutiFlag = 0;
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool _ExceptionFunction_ToMutiline()
{
	int lines = linecountAfterFitter();
	if (lines > 1)
		return true;
	return false;
}
bool _ExceptionFunction_vertial()
{
	if (SEN2020Array[0] &&
		SEN2020Array[1] &&
		SEN2020Array[2] &&
		SEN2020Array[3])
	{
		//LCD_printf("leftCross\n");
		return true;
	}

	if (SEN2020Array[4] &&
		SEN2020Array[5] &&
		SEN2020Array[6] &&
		SEN2020Array[7])
	{
		//LCD_printf("RightCross\n");
		return true;
	}
	return false;
}
bool _ExceptionFunction_IRClose()
{
	if (getFrontIRDataAfterFitter() > 1000)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool _ExceptionFunction_NoLine()
{
	if (linecountAfterFitter() == 0)
	{
		LCD_printf(" NoLine  Triggered!\n");

		return true;
	}
	else
	{
		return false;

	}
}

bool _ExceptionFunction_OneLine()
{
	LCD_printf(" OneLine  Triggered!\n");
	return true;
}
bool _ExceptionFunction_ArriveDoor() 
{
	if (laserIsOnLine(0))
	{
		LCD_printf(" ArriveDoor  Triggered!\n");
		return true;

	}
	return false;
		
}
bool _ExceptionFunction_Bagua()
{
	if (
		SEN2020Array[0] &&

		SEN2020Array[7])
	{
		LCD_printf("bagua\n");
		return true;
	}
	return false;

}
bool _ExceptionFunction_SideClose()
{

}
bool _ExceptionFunction_Click()
{
	return Click_Triggered();
}