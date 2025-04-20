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
		motor_max_speed=100;
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
		if(speed>0){
			if(speed>motor_max_speed){
				set_speed(motor_max_speed);
				motor_speed = motor_max_speed;
			}
			else{
				set_speed(speed);
				motor_speed = speed;
			}
		}
		else{
			if(-speed>motor_max_speed){
				set_speed(-motor_max_speed);
				motor_speed = -motor_max_speed;
			}
			else{
				set_speed(speed);
				motor_speed = speed;
			}
		}
		
    }
	void operator+=(const int8_t& speed){
		if(motor_speed+speed>motor_max_speed){
			set_speed(motor_max_speed);
		}
		else if(motor_speed+speed<-motor_max_speed){
			set_speed(-motor_max_speed);
		}
		else{
			motor_speed+=speed;
		set_speed(motor_speed);
	}
}
void operator-=(const int8_t& speed){
		if(motor_speed-speed>motor_max_speed){
			set_speed(motor_max_speed);
			motor_speed = motor_max_speed;
		}
		else if(motor_speed-speed<-motor_max_speed){
			set_speed(-motor_max_speed);
			motor_speed = -motor_max_speed;
		}
		else{motor_speed = motor_speed-speed;
		set_speed(motor_speed);
		
	}
}
void restore_speed(){
set_speed(motor_speed);
}
void set_max_speed(const int8_t& max_speed){
	if(motor_speed>0){
		if(motor_speed>max_speed){
			set_speed(max_speed);
		}
	}else{
		if(-motor_speed>max_speed){
			set_speed(-max_speed);
		}
	}
	motor_max_speed = max_speed;
}
    private:
    int8_t motor_speed;
	int8_t motor_max_speed;
};
#endif
