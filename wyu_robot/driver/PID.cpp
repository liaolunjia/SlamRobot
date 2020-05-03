#include "PID.h"

PID::PID(float min_val, float max_val, float kp, float ki, float kd)
{
  min_val_ = min_val;
  max_val_ = max_val;
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
}

//经典PID算法，调节PWM波从而控制电机转速
int16_t PID::compute(double setpoint, double measured_value)
{
  double error;	//实际值与目标值的差距
  double pwm;

  //setpoint is constrained between min and max to prevent pid from having too much error
  error = setpoint - measured_value;
  integral_ += error;	//误差的积分
  derivative_ = error - prev_error_;	//相邻两次误差的做差，用于PID的微分运算

  if(setpoint == 0 && error == 0){
    integral_ = 0;
  }

  pwm = (kp_ * error) + (ki_ * integral_) + (kd_ * derivative_);	//PID的运算
  prev_error_ = error;

  return (int16_t)constrain(pwm, min_val_, max_val_);	//将计算出来的PWM占空比值与我们预先设置的阈值做比较，不得超出阈值范围

}

