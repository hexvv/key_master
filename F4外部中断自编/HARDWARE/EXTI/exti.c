//������ûѧλ������������ֻ�������ڰ����Ǹ�IO�ڼ���ƽ�仯��Ȼ���ټ������ж�
//E2 E3 �ߵ�ƽ
//Ԥ�ⰴ����һ��E2��led1��2����
//����������E3��led2��1����
//���� ����
#include "stm32f4xx.h"
#include "exti.h"
#include "key.h"
#include "delay.h"



void EXTIX_Init()
{
	
	EXTI_InitTypeDef EXTI_InitStruct;
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	KEY_Init();   //����E0 E1 IO�� ��Ϊ�ߵ�ƽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE );//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);//E0ӳ�䵽�ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);//E1ӳ�䵽�ж���1
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0 | EXTI_Line1;  //��ʼ�ж���0 1
	EXTI_InitStruct.EXTI_LineCmd=ENABLE; //ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//�����ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//�½���
	
	EXTI_Init(&EXTI_InitStruct);  //��ʼ�ж� 
	
	
		
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;     //�жϷ���0ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;			//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);//��ʼ�жϷ���
	

	
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;//�жϷ���1ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//ͬ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//ͬ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//ͬ��
	
	NVIC_Init(&NVIC_InitStruct);

	
	
}



//led1 ΪF9
//led2 ΪF10

void EXTI0_IRQHandler(void)
{
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)  //����ж����õ�ԭ��������֮���ٽ��е�ƽ�仯�жϣ������Ͳ���������
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


