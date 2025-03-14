#include "stm32f10x.h"
#include "Motor.h"
#define abs(x) ((x)>0?(x):-(x))
volatile int8_t motor3_speed = 0;
volatile int8_t motor4_speed = 0;
void Motor_PWM_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_Cmd(TIM2, ENABLE);
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
}
void Timer_Init(void) {
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 360 - 1;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1|TIM_IT_CC2, ENABLE);
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_Pulse = 0;                
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCStruct);      
	TIM_OC2Init(TIM3, &TIM_OCStruct);  
NVIC_InitTypeDef NVIC_InitStruct;
NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM3, ENABLE);
}
void Motor::set_speed(const int8_t& speed) {
	switch (Motor::motor) {
		case MOTOR2:
			if (speed > 0) {
				TIM_SetCompare1(TIM2, speed);
				TIM_SetCompare2(TIM2, 0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			} else if (speed < 0) {
				TIM_SetCompare2(TIM2, -speed);
				TIM_SetCompare1(TIM2, 0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			} else {
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				TIM_SetCompare1(TIM2, 0);
				TIM_SetCompare2(TIM2, 0);
			}
			break;
		case MOTOR1:
			if (speed > 0) {
				TIM_SetCompare3(TIM2, speed);
				TIM_SetCompare4(TIM2, 0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			} else if (speed < 0) {
				TIM_SetCompare4(TIM2, -speed);
				TIM_SetCompare3(TIM2, 0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			} else {
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_3);
				TIM_SetCompare3(TIM2, 0);
				TIM_SetCompare4(TIM2, 0);
			}
			break;
		case MOTOR3:
			motor3_speed = speed;
			TIM_SetCompare1(TIM3,100-abs(speed));
			break;
		case MOTOR4:
			motor4_speed = speed;
			TIM_SetCompare2(TIM3,100-abs(speed));
			break;
	}
}

