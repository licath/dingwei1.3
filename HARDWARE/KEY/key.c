#include "key.h"
#include "stm32f10x.h"
void key_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能Pc
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //Key->pb5端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉电阻输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->Pc13端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉电阻输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB

}

