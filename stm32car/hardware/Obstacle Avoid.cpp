#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Tracking.h"

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
            turn_left(); // Turn left
        }
    }
     if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)) // Left side obstacle
    {
        Delay_ms(3);
        while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0))
        {
            turn_right(); // Turn right
        }
    }
		 if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)) // Both sides obstacle
    {
        Delay_ms(3);
        while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0) && (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0))
        {
            back(); // Move back
            Delay_ms(600);
            circle_right(); // Circle right
            Delay_ms(500);
        }
    }
}
