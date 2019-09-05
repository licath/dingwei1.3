#include "EXTI.h"
#include "stm32f10x.h"
void Exti4_Init(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA时钟使能
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能复用功能时钟

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0; //4号引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA4
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //GPIOB.4      中断线以及中断初始化配置  下降沿触发
	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6号引脚
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;    //设置成下拉输入
	  GPIO_Init(GPIOA, &GPIO_InitStructure);        //GPIOB6编码器的另一个引脚，用来读取引脚电平

    EXTI_InitStructure.EXTI_Line=EXTI_Line0; 
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            //使能按键KEY0所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //    中断线以及中断初始化配置  下降沿触发
	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6号引脚
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;    //设置成下拉输入
	  GPIO_Init(GPIOA, &GPIO_InitStructure);        //GPIOB6编码器的另一个引脚，用来读取引脚电平
    
		
    EXTI_InitStructure.EXTI_Line=EXTI_Line1; 
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;            //使能按键KEY0所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}
//void Exti3_Init(void)
//{
//	  EXTI_InitTypeDef EXTI_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOA时钟使能
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能复用功能时钟
//	 
//    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
//    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA3
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3); //    中断线以及中断初始化配置  下降沿触发
//	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6号引脚
//	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;    //设置成下拉输入
//	  GPIO_Init(GPIOB, &GPIO_InitStructure);        //GPIOB6编码器的另一个引脚，用来读取引脚电平

//    EXTI_InitStructure.EXTI_Line=EXTI_Line3; 
//	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);   //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;            //使能按键KEY0所在的外部中断通道
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //抢占优先级2
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //子优先级0
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
//    NVIC_Init(&NVIC_InitStructure);       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
//		
//}
