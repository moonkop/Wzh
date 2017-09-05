#ifndef __USART_H
#define __USART_H


void USART1_init(void);

void USART2_init(void);

void USART3_init(void);

void USART4_init(void);

void USART5_init(void);

void USART6_init(void);

void Usart3_Send(u8 *data_to_send, u8 len);
void USART3_SendByByter(u8 Data);
#endif // !__USART_H
