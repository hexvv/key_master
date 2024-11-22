//由于我没学位操作，所以我只有能力在按键那个IO口检测电平变化，然后再激发其中断
//E2 E3 高电平
//预测按按键一（E2）led1亮2不亮
//按按键二（E3）led2亮1不亮
//不按 都灭
#include "stm32f4xx.h"
#include "exti.h"
#include "key.h"
#include "delay.h"



void EXTIX_Init()
{
	
	EXTI_InitTypeDef EXTI_InitStruct;
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	KEY_Init();   //设置E0 E1 IO口 均为高电平
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE );//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);//E0映射到中断线0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);//E1映射到中断线1
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0 | EXTI_Line1;  //初始中断线0 1
	EXTI_InitStruct.EXTI_LineCmd=ENABLE; //使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//触发中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿
	
	EXTI_Init(&EXTI_InitStruct);  //初始中断 
	
	
		
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;     //中断服务0通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;			//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);//初始中断分组
	

	
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;//中断服务1通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//同上
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//同上
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//同上
	
	NVIC_Init(&NVIC_InitStruct);

	
	
}



//led1 为F9
//led2 为F10

void EXTI0_IRQHandler(void)
{
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)  //这个判断设置的原因是消抖之后再进行电平变化判断，这样就不会误判了
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0) 
		{GPIO_ToggleBits(GPIOF,GPIO_Pin_9);}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)
		{GPIO_ToggleBits(GPIOF,GPIO_Pin_10);}
	}

	EXTI_ClearITPendingBit(EXTI_Line1);
}


