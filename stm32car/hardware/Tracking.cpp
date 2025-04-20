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
	right_motor = 50;
	left_motor = -60;
}

void turn_right(void)
{
	right_motor = -60;
	left_motor = 50;
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
{bool is_triggered=false;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 0)
	{left_motor=-100;
	right_motor=-100;
	Delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 0)
	{is_triggered=true;
		turn_right();
	}
	if(is_triggered)
	Delay_ms(70);
	
	}
	else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 1)
	{left_motor=-100;
	right_motor=-100;
	Delay_ms(30);
	bool is_triggered=false;
while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == 1)
{is_triggered=true;
		turn_left();
}
if(is_triggered)
Delay_ms(70);

	}
	else{
		forward();
	}
}
















