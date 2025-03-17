#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include"Delay.h"
extern class Motor right_motor;
extern class Motor left_motor;

void Tracking_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void forward(void)
{
	right_motor = 40;
	left_motor = 40;
}

void turn_left(void)
{
	right_motor = 70;
	left_motor = 0;
}

void turn_right(void)
{
	right_motor = 0;
	left_motor = 70;
}

void back(void)
{
	right_motor = -40;
	left_motor = -40;	
}

void circle_right(void)
{
	turn_right();

}

void Tracking_motion(void)
{
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
	turn_right();
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 1)
	{
		turn_left();
			Delay_ms(200);
	}
}
















