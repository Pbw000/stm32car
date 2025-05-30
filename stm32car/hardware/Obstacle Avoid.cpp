#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Tracking.h"
#include "Motor.h"
#define abs(x) ((x)>0?(x):-(x))
extern class Motor right_motor;
extern class Motor left_motor;
extern uint32_t pulse_width; 
extern uint8_t capture_flag;  
void Obstacle_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_Instructure;
    GPIO_Instructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Instructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
    GPIO_Init(GPIOA, &GPIO_Instructure);
    
}

void BZ(void)
{
    // Removed unused variable BZways

    // if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1)
    // {
    //     forward();
    // }

    if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)) // Right side obstacle
    {
        Delay_ms(3);
        while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0))
        {
 right_motor .set_speed(45);
	left_motor .set_speed( -70);
            Delay_ms(140);
        }
        
    }
    else if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)) // Left side obstacle
    {
        Delay_ms(3);
        while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0))
        {
                left_motor.set_speed( 45);
	right_motor .set_speed( -70);
        Delay_ms(70);
        }
    }
	else if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)) // Both sides obstacle
    {
        Delay_ms(3);
        while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0))
        {
		right_motor .set_speed( 45);
	left_motor .set_speed( -70);
        Delay_ms(70);
        }
    }
}

void Trigger_Sonic(void) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
    Delay_us(2);                      
    GPIO_SetBits(GPIOB, GPIO_Pin_1);  
    Delay_us(15);                    
    GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
}


void Start_Measure(void) {
    TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Disable);        
    TIM3->CNT = 0;                            
    capture_flag = 0;               
    pulse_width = 0;                  
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update | TIM_IT_CC3); 
    TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Enable);          
    Trigger_Sonic();              
}



uint16_t get_dis_count() {
    if (capture_flag) {
        capture_flag = 0;
        return pulse_width ; 
    }
    return 0;
}
void Ultrasonic_Step(){
    uint16_t dis,avr_dis=0;
    static uint16_t pre_dis=10000;
    static bool had_start=false;
    if(!had_start){
        Start_Measure();
        had_start=true;
    }
	dis=get_dis_count();
	if(dis!=0){
        avr_dis=(dis+pre_dis)/2;
        pre_dis=dis;
        had_start=false;
	}
    else return;
    if(avr_dis<800){
			left_motor.set_max_speed(50);
        right_motor.set_max_speed(45);
       left_motor.set_speed(-50);
      right_motor.set_speed(-45);
        Delay_ms(200);
			  left_motor.set_speed(-70);
      right_motor.set_speed(45);
			Delay_ms(100);
    }
    else if(avr_dis<1600){
       left_motor.set_max_speed((avr_dis-400)/20+40);
       right_motor.set_max_speed((avr_dis-400)/20+40);
    }
    else{
        left_motor.set_max_speed(100);
        right_motor.set_max_speed(100);
        left_motor.restore_speed();
        right_motor.restore_speed();
    }
}