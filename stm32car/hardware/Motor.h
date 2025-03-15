#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"                  // Device header
void Motor_PWM_Init(void);
void Timer_Init(void);
void Motor1_set_speed(const int8_t& speed);
void Motor2_set_speed(const int8_t& speed);
void Motor3_set_speed(const int8_t& speed);
void Motor4_set_speed(const int8_t& speed);
class Motor{
  public:   enum Motor_Type{
    MOTOR1,
    MOTOR2,
    MOTOR3,
    MOTOR4
};
    Motor(const Motor_Type& motor_):motor(motor_){
			switch (motor_){
				case MOTOR1:
					set_speed=Motor1_set_speed;
					break;
				case MOTOR2:
					set_speed=Motor2_set_speed;
					break;
				case MOTOR3:
					set_speed=Motor3_set_speed;
					break;
				case MOTOR4:
					set_speed=Motor4_set_speed;
					break;
		
		}}
    void (*set_speed)(const int8_t&);
    void operator=(const int8_t& speed){
        set_speed(speed);
    }
    private:
    Motor_Type motor;
};
#endif
