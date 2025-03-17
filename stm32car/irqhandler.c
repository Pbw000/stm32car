#include "stm32f10x.h"                  // Device header
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) {
			GPIO_SetBits(GPIOB, GPIO_Pin_3);  
    }
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		GPIO_ResetBits(GPIOB, GPIO_Pin_3);  
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	} 
	
TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); 
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}