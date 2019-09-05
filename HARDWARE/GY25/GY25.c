#include"GY25.h"
#include "stdio.h"
#include "stm32f10x.h"
void GY25_USART3_Init(u32 bound1,u32 bound2)
{
	GPIO_InitTypeDef GPIO_InitU3;
	USART_InitTypeDef USART_InitU3;
	NVIC_InitTypeDef NVIC_InitU3;
	USART_InitTypeDef USART_InitStruct2;                        //创建串口1结构体对象
	GPIO_InitTypeDef  GPIO_InitStruct2;                         //创建GPIO1结构体对象
	NVIC_InitTypeDef NVIC_InitStruct2;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //GPIOA时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);     //串口1时钟使能

	GPIO_InitU3.GPIO_Mode=GPIO_Mode_AF_PP;                  //GY25使用串口2
	GPIO_InitU3.GPIO_Pin=GPIO_Pin_10;   //TX
	GPIO_InitU3.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_InitU3);
	
	GPIO_InitU3.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitU3.GPIO_Pin=GPIO_Pin_11;   //RX
  GPIO_Init(GPIOB,&GPIO_InitU3);
	
	GPIO_InitStruct2.GPIO_Mode=  GPIO_Mode_AF_PP;             
  GPIO_InitStruct2.GPIO_Pin= GPIO_Pin_2;   //TX            //数据传输使用串口2
	GPIO_InitStruct2.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStruct2);
	GPIO_InitStruct2.GPIO_Mode=  GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct2.GPIO_Pin= GPIO_Pin_3;   //RX
	GPIO_Init(GPIOA,&GPIO_InitStruct2);                       
	 
	USART_InitU3.USART_BaudRate=bound1;                       
	USART_InitU3.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitU3.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitU3.USART_Parity=USART_Parity_No;
	USART_InitU3.USART_StopBits=USART_StopBits_1;
	USART_InitU3.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitU3);
	USART_Cmd(USART3,ENABLE);
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	USART_InitStruct2.USART_BaudRate=bound2;
	USART_InitStruct2.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct2.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct2.USART_Parity=USART_Parity_No;
	USART_InitStruct2.USART_StopBits=USART_StopBits_1;
  USART_InitStruct2.USART_WordLength=USART_WordLength_8b;	
	USART_Init(USART2,&USART_InitStruct2);
	USART_Cmd(USART2,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	 
	NVIC_InitU3.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitU3.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitU3.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitU3.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitU3);
	
  NVIC_InitStruct2.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct2.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct2.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct2);
}


