#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Button.h"
#include "Buzzer.h"
#include "Light_sensor.h"
#include "Motor.h"
#include "IC.h"
#include "PWM.h"
#include<stdio.h>
#include"Encoder.h"
#include"AD.h"
#include"OLED.h"
#include"m_DMA.h"
#include"USART.h"
volatile int8_t Serial_RxFlag=-1;
volatile uint8_t recvData[2];
void main_init(void){
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
Motor_PWM_Init();
Timer_Init();
CRC_ResetDR();
Bluetooth_Serial_Init();
}

int main(void)
{main_init();
Motor motor1(Motor::MOTOR1);
Motor motor2(Motor::MOTOR2);
Motor motor3(Motor::MOTOR3);
Motor motor4(Motor::MOTOR4);
motor1=50;
motor2=-50;
motor3=50;
motor4=-50;
while(1){
    if(!Serial_RxFlag){
            int v1=recvData[0]-100,v2=recvData[1]-100;
            if(v1<=100&&v2<=100){
            motor1=v1;
            motor2=v2;
            motor3=v1;
            motor4=v2;}
 Serial_RxFlag=-1;
    }
  
   
}
}

