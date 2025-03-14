#include "stm32f10x.h"                  // Device header

void IC_Init(void){
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 65536-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0xF;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	  //TIM_ICInit(TIM3,&TIM_ICInitStructure);
		
		TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    TIM_Cmd(TIM3, ENABLE);
		
		
}

uint16_t get_frequency(void){
return 1000000/(TIM_GetCapture1(TIM3)+1);
}
float get_duty(void){
return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}