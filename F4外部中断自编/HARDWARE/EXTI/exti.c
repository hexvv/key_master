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
	
	
	KEY_Init();   //设置E2 E3 IO口 均为高电平
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE );//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);//E2映射到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);//E3映射到中断线3
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3 | EXTI_Line2;  //初始中断线2，3
	EXTI_InitStruct.EXTI_LineCmd=ENABLE; //使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//触发中断
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿
	
	EXTI_Init(&EXTI_InitStruct);  //初始中断 
	
	
		
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;     //中断服务2通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;			//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);//初始中断分组
	

	
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;//中断服务3通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//同上
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//同上
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//同上
	
	NVIC_Init(&NVIC_InitStruct);

	
	
}



//led1 为F9
//led2 为F10

void EXTI2_IRQHandler(void)
{
	delay_ms(20);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)  //这个判断设置的原因是消抖之后再进行电平变化判断，这样就不会误判了
	{
	GPIO_ToggleBits(GPIOF,GPIO_Pin_9);
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	delay_ms(20);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)
	{
	GPIO_ToggleBits(GPIOF,GPIO_Pin_10);
	}

	EXTI_ClearITPendingBit(EXTI_Line3);
}


