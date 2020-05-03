#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "config.h"

#define abs(a,b) \
((a > b) ? (a-b) : (b-a))

class Motor {
	public:
		double rpm;

		Motor(Motor_TypeDef _motor);
		void spin(int16_t pwm);	//电机运行
		void updateSpeed();	//通过编码器计算出当前速度
		uint32_t get_last_tick();	//获取编码器上一时刻的刻度值
	
	private:
		Motor_TypeDef motor;	//电机ID

		int32_t tick_last;	//编码器上一时刻刻度值
		int32_t last_milli_time;	//上一次读取编码器数值的时间
		double delta_mins_time;	//两次编码器读取时间间隔
		
};

#endif //_MOTOR_H_