#ifndef __RESPCOM_H
#define __RESPCOM_H
#include "stm32f4xx.h"


void RaspiImportData(u8 data);

void RaspiSendRequest(u8 request);

void getRaspiOnlineStatus();
void readQRcode();
void readQRcode1();
void raspiPrintResponse();

extern u8 QrReadReqeusetFlag;
extern u8 respidata;


#endif // !__RESPCOM_H

