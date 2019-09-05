#ifndef __GY25_H
#define __GY25_H
#include "stdio.h"
#include "stm32f10x.h"

extern int  YAW;
extern uint8_t flag;
extern uint8_t USART_RX_BUF[200];     //接收缓冲,最大63个字节.末字节为换行符 

void SentInit(void);
void uart_init(uint32_t bound);
void GY25_USART3_Init(u32 bound1,u32 bound2);

#endif

