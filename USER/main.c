#include <stdio.h> 
#include <stdlib.h> 
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "EXTI.h"
#include "GY25.h"
#include "time.h"
#include "math.h"
#include "key.h"
#include "main.h"

long count_l=0;
long count_r=0;
int YAW,_YAW,dYAW=0;
double R_count,L_count,R_counter=0,L_counter=0;  //过渡数值
double R,L,dR,dL,p;
float K_r=0.9588,K_l=1.0449;
int x,y;  
int _flag;
u16 data[9]={0xAA,0,0,0,0,0,0,0,0x55};

void SoftReset()    //复位程序
{
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}

	void Clear_YAW()
{  
	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_SendData(USART3, 0xA5);   
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	USART_SendData(USART3, 0x55);  
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
	USART_SendData(USART3, 0xA5);   
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	USART_SendData(USART3, 0x52);   
}

void DingWei()          //由编码器与陀螺仪得到位置的信息
{
	p=YAW*PI/180;
	R_count=count_r;
	L_count=count_l;
	dR=(R_count-R_counter);
	dL=(L_count-L_counter);
	R=dR/pulses*wheel*PI;
	L=dL/pulses*wheel*PI;
  x+=R*sin(p-PI/4)-L*cos(p-PI/4);
	y+=R*cos(p-PI/4)+L*sin(p-PI/4);
	R_counter=R_count;
	L_counter=L_count;
}                           //主要算法

void ClearData(void)
{
				if(-45<_YAW<45)
					dYAW=0;
				if(45<_YAW<135)
					dYAW=90;
				if(135<_YAW||_YAW<-135)
					dYAW=180;
				if(-135<_YAW<-45)
				 dYAW=-90;
	 count_r=0;
	 count_l=0;
	 Clear_YAW();
	}

void USART3_IRQHandler(void)                	//串口2中断服务程序
	{
	static uint8_t k=0,rebuf[8]={0};
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
		{
		 rebuf[k++] =USART_ReceiveData(USART3);	//读取接收到的数据
		 if(!(rebuf[0]==0xaa))//如果帧头错误，清缓存
		 {
			k=0;
			rebuf[0]=0;
		 }
		 if(k==8)//数据接收完毕
		 {
			if(rebuf[7]==0x55)//判断帧尾，正确则解析姿态角
			{
			 _YAW=(rebuf[1]<<8|rebuf[2]);//YAW，PITCH,ROLL为真实值的100倍
				_YAW=_YAW/100;
				if(_YAW>455)
					_YAW-=655;
				else
					_YAW=_YAW;
			}
			k=0;//清缓存
		 }
    } 
} 

//void USART2_IRQHandler(void)                	//串口2中断接受数据
//{
//	static uint8_t k=0,rebuf[6]={0};
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//		{
//     rebuf[k++] =USART_ReceiveData(USART3);	//读取接收到的数据
//		 if(!(rebuf[0]==0x55))//如果帧头错误，清缓存
//		 {
//			k=0;
//			rebuf[0]=0;	
//		 }
//		 if(k==6)//数据接收完毕
//		 {
//			if(rebuf[5]==0xAA)//判断帧尾，正确则解析姿态角
//			{
//			 x=(rebuf[1]<<8|rebuf[2]);
//			 y=(rebuf[3]<<8|rebuf[4]);
//			}
//     }
//    }
//}

void USART2_IRQHandler(void)                	//串口2中断接受数据
{
	char i; 
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
		i= USART_ReceiveData(USART2);
		 if(i=='r')
		 {
			SoftReset();
		 }
		}
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);	//清除接收中断标志
}
void Sent_data(u16* str, u8 len)
{
  u8 i;
  data[1]=x>>8;
	data[2]=x;
	data[3]=y>>8;
  data[4]=y;
	data[5]=YAW>>8;
	data[6]=YAW;
	data[7]=_flag;
	for( i=0;i<len;i++)
  { 
   USART_SendData(USART2,str[i]); 
   while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		delay_ms(1);
  }
}

 void EXTI0_IRQHandler(void)
 {
	 if( GPIOA->IDR& GPIO_IDR_IDR5)
		 count_r--;
	 else
		 count_r++;
   EXTI_ClearITPendingBit(EXTI_Line0);
 }

 void EXTI1_IRQHandler(void)
 {
	   if( GPIOA->IDR& GPIO_IDR_IDR6)
		 count_l++;
	   else
	 	 count_l--;
     EXTI_ClearITPendingBit(EXTI_Line1);
 }

 int main(void)
 {
	key_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// 设置中断优先级分组2
  uart_init(9600);
	delay_init();	    	 //延时函数初始化	 	 	 
	LED_Init();		  	//初始化与LED连接的硬件接口
	Exti4_Init();
	GY25_USART3_Init(115200,9600);  //前一个为GY25的波特率，后一个为数据传输串口的波特率
	Clear_YAW();
	while(1)
	{

	  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)==0&&GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==0)
		{
			_flag=1;
	  }
		else
			_flag=0;
		if(_flag==1)
	  {
			static long i=0;
			i++;
			if(i==1)
	  	ClearData();
	  }
	  if(_flag==0)
		{
			YAW=_YAW+dYAW;
					if(YAW>=180)
					{
						YAW-=360;
					}
						if(YAW<=-180)
					{
						YAW+=360;
					}
	    DingWei();
			Sent_data(data,9);
		}			
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)==0)
		{
			LED0=0;
			SoftReset();
		}
    else
			LED0=1;
		printf("%ld   %ld   %d   %d   %d\n",count_r,count_l,YAW,x,y);
  }
}
