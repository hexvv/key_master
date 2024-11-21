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
	
	
	KEY_Init();   //����E2 E3 IO�� ��Ϊ�ߵ�ƽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE );//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);//E2ӳ�䵽�ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);//E3ӳ�䵽�ж���3
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3 | EXTI_Line2;  //��ʼ�ж���2��3
	EXTI_InitStruct.EXTI_LineCmd=ENABLE; //ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//�����ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//�½���
	
	EXTI_Init(&EXTI_InitStruct);  //��ʼ�ж� 
	
	
		
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;     //�жϷ���2ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;			//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);//��ʼ�жϷ���
	

	
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;//�жϷ���3ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//ͬ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//ͬ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//ͬ��
	
	NVIC_Init(&NVIC_InitStruct);

	
	
}



//led1 ΪF9
//led2 ΪF10

void EXTI2_IRQHandler(void)
{
	delay_ms(20);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)  //����ж����õ�ԭ��������֮���ٽ��е�ƽ�仯�жϣ������Ͳ���������
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


