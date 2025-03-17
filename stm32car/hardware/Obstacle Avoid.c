#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Tracking.h"

void Obstacle_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_Instructure;
    GPIO_Instructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Instructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
    GPIO_Init(GPIOA,&GPIO_Instructure);
}

void BZ(void)
{
    uint8_t BZways = 0;
    
    if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15) == 1 && GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12) == 1)
    {
        forward();
    }
    if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15) == 1)&&(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12) == 0))                //右边感应到障碍物
  {
        Delay_ms(3);
        if(((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)==1)&&(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)) == 0))
        {
            turn_left();                                  //左转
        }          
  }                               
  if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==1)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))             //左边感应到障碍物
  {
        Delay_ms(3);
        if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==1)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))              
        {          
            turn_right();                                  //右转     
        }
  }
  if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==0)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))             //左右两边同时感应到障碍物
  {
        Delay_ms(3);
        if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==0)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))              
        {          
            back();                                        //后退         
            Delay_ms(600);                                 
            circle_right();                              //转一个角度         
            Delay_ms(500);
        }
  }
}
