#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "Tracking.h"
#include"m_DMA.h"
#include"USART.h"
#include"Obstacle Avoid.h"
volatile int8_t Serial_RxFlag=-1;
volatile uint8_t recvData[3];

uint8_t Compute_CRC8(uint8_t data1, uint8_t data2) {
    CRC_ResetDR();
    uint32_t input = ((uint32_t)data1 << 24) | ((uint32_t)data2 << 16);
    CRC_CalcCRC(input);
    return (uint8_t)(CRC_GetCRC() & 0xFF);
}


void main_init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
Motor_PWM_Init();
CRC_ResetDR();
Bluetooth_Serial_Init();
Tracking_Init();
Obstacle_Init();
DMA_init();
}
bool tracking_flag=false;
bool obstacle_flag=false;
Motor right_motor(Motor::Right_Motor);
Motor left_motor(Motor::Left_Motor);
int main(void)
{main_init();
while(1){
   Ultrasonic_Step();
    if(tracking_flag){
        Tracking_motion();
    }
    if(obstacle_flag){
        BZ();
    }
    if(!Serial_RxFlag){
        if (recvData[2] != Compute_CRC8(recvData[0], recvData[1])){
            Serial_RxFlag=-1;
            continue;
        }
        int v1=recvData[0]-100,v2=recvData[1]-100;
        if(v1<=100&&v2<=100){
            left_motor=v1;
            right_motor=v2;
            tracking_flag=false;
}
else if(v1==101&&v2==100){
     //启动循迹
     tracking_flag=true;
     start_transfer();
}
else if(v1==101&&v2==101){
     //打开避障
     obstacle_flag=true;
     start_transfer();
}
else if(v1==101&&v2==102){
    //关闭避障
    obstacle_flag=false;
    start_transfer();
}
Serial_RxFlag=-1;
}

}}


