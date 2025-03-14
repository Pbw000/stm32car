#include "stm32f10x.h"
GPIO_TypeDef* l_GPIOx;
uint16_t l_GPIO_Pin;
void Light_sensor_init(GPIO_TypeDef* l_GPIOx_, uint16_t l_GPIO_Pin_){
    l_GPIOx = l_GPIOx_;
    l_GPIO_Pin = l_GPIO_Pin_;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = l_GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(l_GPIOx, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line6;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
}

uint8_t isLightOn(void){
    return !GPIO_ReadInputDataBit(l_GPIOx, l_GPIO_Pin);
}
