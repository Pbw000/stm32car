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
    if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15) == 1)&&(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12) == 0))                //�ұ߸�Ӧ���ϰ���
  {
        Delay_ms(3);
        if(((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)==1)&&(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)) == 0))
        {
            turn_left();                                  //��ת
        }          
  }                               
  if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==1)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))             //��߸�Ӧ���ϰ���
  {
        Delay_ms(3);
        if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==1)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))              
        {          
            turn_right();                                  //��ת     
        }
  }
  if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==0)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))             //��������ͬʱ��Ӧ���ϰ���
  {
        Delay_ms(3);
        if((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)==0)&&((GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15))==0))              
        {          
            back();                                        //����         
            Delay_ms(600);                                 
            circle_right();                              //תһ���Ƕ�         
            Delay_ms(500);
        }
  }
}
