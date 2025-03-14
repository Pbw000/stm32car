#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"                  // Device header
void Motor_PWM_Init(void);
void Timer_Init(void);
class Motor{
  public:   enum Motor_Type{
    MOTOR1,
    MOTOR2,
    MOTOR3,
    MOTOR4
};
    Motor(const Motor_Type& motor_):motor(motor_){}
    void set_speed(const int8_t& speed);
    void operator=(const int8_t& speed){
        set_speed(speed);
    }
    private:
    Motor_Type motor;
};
#endif
