#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
uint16_t count=0;
void Button_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line5;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_Init(&NVIC_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line8);
}


