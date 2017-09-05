
#include "RespCom.h"
#include "USART.h"
//#include "main.h"
#include "preProcesser.h"
#include "LCD_print.h"
//#include "..\RESPCOM.H"
u8 respidata = 0;
u8 respiRespondFlag = 0;

u8 QrWaitingFlag = 0;
u8 QrReadReqeusetFlag = 0;
u8 QrReadReqeusetSendedFlag = 0;

void RaspiImportData(u8 data)
{
	respidata = data;
	respiRespondFlag = 1;
	LCD_printf("qrcode=%d", data);

}
void RaspiSendRequest(u8 request)
{
	USART_SendData(USART1, request);
	respiRespondFlag = 0;
	respidata = 0;
}

void getRaspiOnlineStatus()
{
	if (QrWaitingFlag)
	{
		return;
	}
	RaspiSendRequest(0x01);
}
void readQRcode()
{
	if (QrReadReqeusetFlag)
	{
		if (!QrReadReqeusetSendedFlag)
		{
			RaspiSendRequest(0x02);
			QrReadReqeusetSendedFlag = 1;
		}
		QrWaitingFlag = 1;
	}
}

void readQRcode1() {
	RaspiSendRequest(0x02);
}

void raspiPrintResponse()
{
	if (respiRespondFlag == 1)
	{
		if (QrWaitingFlag == 1)
		{
			LCD_printf("QRcode: %d\n", respidata);
			QrReadReqeusetSendedFlag = 0;
			QrWaitingFlag = 0;
		}
		else
		{
			LCD_printf("Respi: %d\n", respidata);
		}
	}
}
