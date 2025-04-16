#include "stm32f10x.h"
#include "Motor.h"
#define abs(x) ((x)>0?(x):-(x))
volatile int8_t left_motor_speed = 0;
volatile int8_t right_motor_speed = 0;
void Motor_PWM_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // ????
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); // Disable JTAG-DP, enable SW-DP
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_Period = 10000;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3, ENABLE);
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_Pulse = 0;                
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCStruct);      
	TIM_OC2Init(TIM3, &TIM_OCStruct);  
	 TIM_ICInitTypeDef TIM_ICStruct;
    TIM_ICStruct.TIM_Channel = TIM_Channel_3;      // TIM3_CH3??PB0
    TIM_ICStruct.TIM_ICPolarity = TIM_ICPolarity_Rising; // ???????
    TIM_ICStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1; // ???
    TIM_ICStruct.TIM_ICFilter = 0x0;               // ???
    TIM_ICInit(TIM3, &TIM_ICStruct);
NVIC_InitTypeDef NVIC_InitStruct;
NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStruct);
TIM_Cmd(TIM3, ENABLE);
}

void left_motor_set_speed(const int8_t& speed){
	if (speed > 0) {
		//GPIO_SetBits(GPIOB, GPIO_Pin_3);
		TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);
		TIM_SetCompare1(TIM3, (100-speed)*100);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	} else if (speed < 0) {
		//GPIO_SetBits(GPIOB, GPIO_Pin_3);
		TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);
		TIM_SetCompare1(TIM3, (100+speed)*100);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	} else {	
		TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Disable);
		GPIO_ResetBits(GPIOB, GPIO_Pin_3);  
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		
	}
}

void right_motor_set_speed(const int8_t& speed){
	if (speed < 0) {
		//GPIO_SetBits(GPIOC, GPIO_Pin_13);
		TIM_CCxCmd(TIM3, TIM_Channel_2, TIM_CCx_Enable);
		TIM_SetCompare2(TIM3, (100+speed)*100);
		
GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	} else if (speed > 0) {
		//GPIO_SetBits(GPIOC, GPIO_Pin_13);
		TIM_CCxCmd(TIM3, TIM_Channel_2, TIM_CCx_Enable);
		TIM_SetCompare2(TIM3, (100-speed)*100);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
	} else {	
		TIM_CCxCmd(TIM3, TIM_Channel_2, TIM_CCx_Disable);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		
GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}