#include "sent.h"
#include "stm32f10x.h"
void SentInit()
{
	 USART_InitTypeDef USART_InitStruct2;                        //创建串口1结构体对象
	 GPIO_InitTypeDef  GPIO_InitStruct;                         //创建GPIO1结构体对象
	 NVIC_InitTypeDef  NVIC_InitStruct;                         //创建中断1结构体对象

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //GPIOA时钟使能
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);     //串口1时钟使能

	 GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_AF_PP;             //1.不同的模式分开初始化
	 GPIO_InitStruct.GPIO_Pin= GPIO_Pin_2;   //TX
	 GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz ;
	 GPIO_Init(GPIOA,&GPIO_InitStruct);
	 GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_IN_FLOATING;
	 GPIO_InitStruct.GPIO_Pin= GPIO_Pin_3;   //RX
	 GPIO_Init(GPIOA,&GPIO_InitStruct);                        //2.上拉浮空输入不需要输出频率
	
	 USART_InitStruct2.USART_BaudRate=115200;
	 USART_InitStruct2.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	 USART_InitStruct2.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	 USART_InitStruct2.USART_Parity=USART_Parity_No;
	 USART_InitStruct2.USART_StopBits=USART_StopBits_1;
   USART_InitStruct2.USART_WordLength=USART_WordLength_8b;	
	 USART_Init(USART2,&USART_InitStruct2);
	 USART_Cmd(USART2,ENABLE);
	 USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

   NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
   NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
   NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
   NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
   NVIC_Init(&NVIC_InitStruct);

}

