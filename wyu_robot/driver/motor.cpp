#include "motor.h"

//uint32_t  MOTOR_PWM_TIM_CHANNEL[MOTORn] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4,};
//GPIO_TypeDef* MOTOR_IN1_PORT[MOTORn] = {AIN1_GPIO_Port, BIN1_GPIO_Port, CIN1_GPIO_Port, DIN1_GPIO_Port};
//GPIO_TypeDef* MOTOR_IN2_PORT[MOTORn] = {AIN2_GPIO_Port, BIN2_GPIO_Port, CIN2_GPIO_Port, DIN2_GPIO_Port};
//uint16_t  MOTOR_IN1_PIN[MOTORn] = {AIN1_Pin, BIN1_Pin, CIN1_Pin, DIN1_Pin};
//uint16_t  MOTOR_IN2_PIN[MOTORn] = {AIN2_Pin, BIN2_Pin, CIN2_Pin, DIN2_Pin};

Motor::Motor(Motor_TypeDef _motor)
{
	motor = _motor;

	tick_last = 0;
	last_milli_time = 0;
	delta_mins_time = 0;
}

//电机运行
void Motor::spin(int16_t pwm)
{
	if(this->motor==MOTORA)
	{
		if(pwm >= 0)
			{
				HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwm);	
			}else if(pwm <= 0){
				HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,-pwm);	
			}
		
	}else if(this->motor==MOTORB)
	{
		if(pwm >= 0)
			{
				HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,pwm);	
			}else if(pwm <= 0){
				HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,-pwm);	
			}
		
	}else if(this->motor==MOTORC)
	{
		if(pwm >= 0)
			{
				HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,pwm);
			}else if(pwm <= 0){
				HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,-pwm);
			}
			
	}else if(this->motor==MOTORD)
	{
		if(pwm >= 0)
			{
				HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,pwm);	
			}else if(pwm <= 0){
				HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,-pwm);	
			}
		
	}
}

//更新速度，通过编码器计算出当前速度
void Motor::updateSpeed()
{	
	double tick_inc;
	int32_t tick_cur;
	int32_t cur_milli_time = HAL_GetTick();
	
  if(this->motor==MOTORA){tick_cur = (int32_t)__HAL_TIM_GET_COUNTER(&htim3); }
		else if(this->motor==MOTORB){tick_cur = (int32_t)__HAL_TIM_GET_COUNTER(&htim4); }
		else if(this->motor==MOTORC){tick_cur = (int32_t)__HAL_TIM_GET_COUNTER(&htim5); }
		else if(this->motor==MOTORD){tick_cur = (int32_t)__HAL_TIM_GET_COUNTER(&htim8); };		
		
	if(abs(tick_cur,tick_last ) > 30000)		//差值过大，说明溢出
	{ 
		if(tick_cur > tick_last )							//反转	
		{										
			tick_inc = tick_cur - 65536 - tick_last ;
		}else{																			//正转
			tick_inc = 65536 - tick_last + tick_cur ;
		}

	}else{
		tick_inc  = tick_cur - tick_last ;
	 }

	if(this->motor==MOTORA || this->motor==MOTORC){tick_inc = tick_inc * (-1); }
	delta_mins_time = (double)(cur_milli_time - last_milli_time) / 60000;	
	rpm = tick_inc / 780 / delta_mins_time ;

	tick_last = tick_cur ;
	last_milli_time = cur_milli_time ;
}
//	if(pwm >= 0)
//			{
//				HAL_GPIO_WritePin(MOTOR_IN2_PORT[this->motor], MOTOR_IN2_PIN[this->motor], GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(MOTOR_IN1_PORT[this->motor], MOTOR_IN1_PIN[this->motor], GPIO_PIN_SET);
//			}else if(pwm <= 0){
//				HAL_GPIO_WritePin(MOTOR_IN1_PORT[this->motor], MOTOR_IN1_PIN[this->motor], GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(MOTOR_IN2_PORT[this->motor], MOTOR_IN2_PIN[this->motor], GPIO_PIN_SET);
//			}
//		__HAL_TIM_SET_COMPARE(&htim1,MOTOR_PWM_TIM_CHANNEL[this->motor],pwm);	
