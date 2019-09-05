#include "time.h"
#include "led.h"
#include "stm32f10x.h"
void TIM_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period= arr;
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//设定中断向量   本程序为TIM4的中断
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能响应中断向量的中断响应
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//配置中断向量的抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//配置中断向量的响应优先级
	NVIC_Init(&NVIC_InitStructure);//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


