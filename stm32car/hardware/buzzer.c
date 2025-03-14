#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "buzzer.h"
GPIO_TypeDef* GPIOx;
uint16_t GPIO_Pin;
void on(void){
    GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
}

void off(void){
    GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
}

void buzz_ms(uint16_t ms){
    on();
    Delay_ms(ms);
    off();
}

void Buzzer_init(GPIO_TypeDef* GPIOx_, uint16_t GPIO_Pin_){
    GPIOx = GPIOx_;
    GPIO_Pin = GPIO_Pin_;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
   off();
}
