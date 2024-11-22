#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "misc.h"


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	LED_Init();
	KEY_Init();
	EXTIX_Init();
	delay_init(168);
	
	
	while(1)
	{
		
	
	}
	
	
	
	
	
	
	
	
	
}

