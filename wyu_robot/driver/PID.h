#ifndef PID_H
#define PID_H

#include "config.h"

//设置转速阈值
#define constrain(amt,low,high) \
	((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

class PID
{
  public:
    PID(float min_val, float max_val, float kp, float ki, float kd);
    int16_t compute(double setpoint, double measured_value);	//计算出PWM波
//    void updateConstants(float kp, float ki, float kd);

  private:
    float min_val_;
    float max_val_;

		float kp_;
    float ki_;
    float kd_;
	
    double integral_;	//误差的积分值
    double derivative_;	//两次误差的差值（还不太理解这个变量的物理意义）
    double prev_error_;	//上一次误差
};

#endif
