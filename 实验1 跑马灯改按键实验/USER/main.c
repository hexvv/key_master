#include "stm32f4xx.h"
#include "key.h"
#include "led.h"
#include "delay.h"




uint8_t NUM;    //在这里定义如果是num=1，那是不是永远都是1？怎么变都变不了
int main(void)
{ 
	LED_Init();
	KEY_Init();
	delay_init(168);
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
	while(1)
	{
		delay_ms(50);
		NUM=KeynumGet(); 
		
		if(NUM==1)
		{
			delay_ms(10);
			if(NUM==1)
			LED_Turn();
			delay_ms(50);
		}
		else
		{}
	
	
	
	
	
	}
	
	
	
}


/**
*******************下面注释掉的代码是通过 位带 操作实现IO口控制**************************************
	
int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
  while(1)
	{
     LED0=0;			  //LED0亮
	   LED1=1;				//LED1灭
		 delay_ms(500);
		 LED0=1;				//LED0灭
		 LED1=0;				//LED1亮
		 delay_ms(500);
	 }
}
**************************************************************************************************
 **/	
	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOF->BSRRH=GPIO_Pin_9;//LED0亮
	   GPIOF->BSRRL=GPIO_Pin_10;//LED1灭
		 delay_ms(500);
     GPIOF->BSRRL=GPIO_Pin_9;//LED0灭
	   GPIOF->BSRRH=GPIO_Pin_10;//LED1亮
		 delay_ms(500);

	 }
 }	 
**************************************************************************************************
**/	
 



