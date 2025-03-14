#include "stm32f10x.h"                  // Device header
extern int8_t motor3_speed;
extern int8_t motor4_speed;
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) {
        if(motor3_speed<0){
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
		else if(motor3_speed>0){
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		}
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); 
    }
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET) {
		if(motor4_speed<0){
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
		else if(motor4_speed>0){
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); 
    }
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		if(motor3_speed<100){
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);}
		if(motor4_speed<100){
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}