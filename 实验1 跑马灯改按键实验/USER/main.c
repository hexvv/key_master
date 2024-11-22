#include "stm32f4xx.h"
#include "key.h"
#include "led.h"
#include "delay.h"




uint8_t NUM;    //�����ﶨ�������num=1�����ǲ�����Զ����1����ô�䶼�䲻��
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
*******************����ע�͵��Ĵ�����ͨ�� λ�� ����ʵ��IO�ڿ���**************************************
	
int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
  while(1)
	{
     LED0=0;			  //LED0��
	   LED1=1;				//LED1��
		 delay_ms(500);
		 LED0=1;				//LED0��
		 LED1=0;				//LED1��
		 delay_ms(500);
	 }
}
**************************************************************************************************
 **/	
	
/**
*******************����ע�͵��Ĵ�����ͨ�� ֱ�Ӳ����Ĵ��� ��ʽʵ��IO�ڿ���**************************************
int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
     GPIOF->BSRRH=GPIO_Pin_9;//LED0��
	   GPIOF->BSRRL=GPIO_Pin_10;//LED1��
		 delay_ms(500);
     GPIOF->BSRRL=GPIO_Pin_9;//LED0��
	   GPIOF->BSRRH=GPIO_Pin_10;//LED1��
		 delay_ms(500);

	 }
 }	 
**************************************************************************************************
**/	
 



