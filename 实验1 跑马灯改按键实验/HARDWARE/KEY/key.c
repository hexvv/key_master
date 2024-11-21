#include "key.h"
#include "stm32f4xx.h"
#include "delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);//上拉输入

}

uint8_t KeynumGet(void)
{
	uint8_t num=0;
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
	{
		delay_ms(50);
		num=1;
		return num;      //按键按下
	
	}
	else
	{
		

		return num;   

	}

}

