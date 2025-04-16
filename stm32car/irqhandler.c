#include "stm32f10x.h"                  // Device header
volatile uint32_t pulse_width = 0; 
volatile uint8_t capture_flag = 0;  
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
		if(!pulse_width)pulse_width = 0xFFFFFFFF;
capture_flag = 1;
 TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Disable);    
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	} 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		if(!pulse_width)pulse_width = 0xFFFFFFFF;
capture_flag = 1;
 TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Disable);    
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
if (TIM_GetITStatus(TIM3, TIM_IT_CC3) == SET) {
if (TIM3->CCER & TIM_CCER_CC3P) {
pulse_width = TIM_GetCapture3(TIM3);
TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Rising);
} else {
	pulse_width=0;
TIM3->CNT = 0;    
TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Falling);
}
TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
}
TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); 
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}