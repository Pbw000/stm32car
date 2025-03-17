#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"                  // Device header
void Motor_PWM_Init(void);
void right_motor_set_speed(const int8_t& speed);
void left_motor_set_speed(const int8_t& speed);
class Motor{
  public:   enum Motor_Type{
    Right_Motor,
	Left_Motor
};
    Motor(const Motor_Type& motor_){
			switch (motor_){
				case Right_Motor:
					set_speed=right_motor_set_speed;
					break;
				case Left_Motor:
					set_speed=left_motor_set_speed;
					break;
		
		}}
    void (*set_speed)(const int8_t&);
    void operator=(const int8_t& speed){
        set_speed(speed);
		motor_speed = speed;
    }
	void operator+=(const int8_t& speed){
		if(motor_speed+speed>100){
			set_speed(100);
		}
		else if(motor_speed+speed<-100){
			set_speed(-100);
		}
		else{
			motor_speed+=speed;
		set_speed(motor_speed);
	}
}
void operator-=(const int8_t& speed){
		if(motor_speed-speed>100){
			set_speed(100);
			motor_speed = 100;
		}
		else if(motor_speed-speed<-100){
			set_speed(-100);
			motor_speed = -100;
		}
		else{motor_speed = motor_speed-speed;
		set_speed(motor_speed);
		
	}
}
    private:
    int8_t motor_speed;
};
#endif
