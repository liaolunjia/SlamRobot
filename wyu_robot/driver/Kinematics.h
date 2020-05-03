#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "config.h"

class Kinematics
{
  public:
    struct rpm {
      double motorA_rpm;	//A轮转速
      double motorB_rpm;	//B轮转速
			double motorC_rpm;	//C轮转速
			double motorD_rpm;	//D轮转速		
    };
    struct velocities {
      float linear_x;
      float linear_y;
      float angular_z;
    };
    Kinematics(float wheel_diameter, float base_width,float _base_long);
    Kinematics::rpm Velocities_to_rpm(float liner_vel_x,float liner_vel_y,float angular_rad_z);//将线速度转换成各个轮子转速
		Kinematics::velocities rpm_to_Velocities(double motor_a_rpm, double motor_b_rpm, double motor_c_rpm, double motor_d_rpm);//从各轮子转速推算出底盘的线速度
//		int rpm_to_PWM(int rpm);
  private:
    float linear_vel_x_min;	//X轴线速度
    float linear_vel_y_min;	//Y轴线速度（用差速轮时Y轴速度恒为零 ，这个变量为麦克纳木轮准备的）
    float angular_rad_z_min;	//Z轴角速度
    float circumference;	//轮子周长
    float tangential_vel;	//轮子切向速度
    float wheel_diameter;	//轮子直径
    float base_width;	//底盘左右两轮子的间隔
		float base_long;  //底盘前后两轮子的间隔
};

#endif
