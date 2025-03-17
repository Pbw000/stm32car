#include "stm32f10x.h"                  // Device header
#include "Motor.h"
extern class Motor right_motor(Motor::Right_Motor);
extern class Motor left_motor(Motor::Left_Motor);
void Tracking_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 1)
	{
		forward();
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 0)
	{
		forward();
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 0)
	{
		turn_left();
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 1)
	{
		turn_right();
	}
}