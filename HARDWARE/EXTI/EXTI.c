#include "EXTI.h"
#include "stm32f10x.h"
void Exti4_Init(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOAʱ��ʹ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //ʹ�ܸ��ù���ʱ��

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0; //4������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA4
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //GPIOB.4      �ж����Լ��жϳ�ʼ������  �½��ش���
	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6������
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;    //���ó���������
	  GPIO_Init(GPIOA, &GPIO_InitStructure);        //GPIOB6����������һ�����ţ�������ȡ���ŵ�ƽ

    EXTI_InitStructure.EXTI_Line=EXTI_Line0; 
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;            //ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //    �ж����Լ��жϳ�ʼ������  �½��ش���
	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6������
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;    //���ó���������
	  GPIO_Init(GPIOA, &GPIO_InitStructure);        //GPIOB6����������һ�����ţ�������ȡ���ŵ�ƽ
    
		
    EXTI_InitStructure.EXTI_Line=EXTI_Line1; 
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;            //ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}
//void Exti3_Init(void)
//{
//	  EXTI_InitTypeDef EXTI_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOAʱ��ʹ��
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //ʹ�ܸ��ù���ʱ��
//	 
//    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
//    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA3
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3); //    �ж����Լ��жϳ�ʼ������  �½��ش���
//	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; //6������
//	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;    //���ó���������
//	  GPIO_Init(GPIOB, &GPIO_InitStructure);        //GPIOB6����������һ�����ţ�������ȡ���ŵ�ƽ

//    EXTI_InitStructure.EXTI_Line=EXTI_Line3; 
//	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);   //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;            //ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //��ռ���ȼ�2
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   //�����ȼ�0
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //ʹ���ⲿ�ж�ͨ��
//    NVIC_Init(&NVIC_InitStructure);       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
//		
//}
