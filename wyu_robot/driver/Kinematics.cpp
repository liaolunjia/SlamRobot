#include "Kinematics.h"

Kinematics::Kinematics(float _wheel_diameter, float _base_width,float _base_long)
{
    wheel_diameter = _wheel_diameter;
    circumference = PI * wheel_diameter;
    base_width = _base_width;
	  base_long = _base_long;
}

//将线速度转换成各个轮子转速
Kinematics::rpm Kinematics::Velocities_to_rpm(float liner_vel_x,float liner_vel_y,float angular_rad_z)
{
	linear_vel_x_min = liner_vel_x * 60;
	linear_vel_y_min = liner_vel_y * 60;
	angular_rad_z_min = angular_rad_z * 60;
	
	tangential_vel = angular_rad_z_min * ( (base_width/2) + (base_long/2) );
  
	Kinematics::rpm rpm;
	rpm.motorA_rpm = (linear_vel_x_min - linear_vel_y_min - tangential_vel) / circumference ;
	rpm.motorB_rpm = (linear_vel_x_min + linear_vel_y_min + tangential_vel) / circumference ;
	rpm.motorC_rpm = (linear_vel_x_min + linear_vel_y_min - tangential_vel) / circumference ;
	rpm.motorD_rpm = (linear_vel_x_min - linear_vel_y_min + tangential_vel) / circumference ;
	
	return rpm;
}

//从各轮子转速推算出底盘的线速度
Kinematics::velocities Kinematics::rpm_to_Velocities(double motor_a_rpm, double motor_b_rpm, double motor_c_rpm, double motor_d_rpm)
{
	Kinematics::velocities vel;
	vel.linear_x = (float)(motor_a_rpm + motor_b_rpm + motor_c_rpm + motor_d_rpm) * circumference / 4 / 60 ; 
	vel.linear_y = (float)(-motor_a_rpm + motor_b_rpm + motor_c_rpm - motor_d_rpm) * circumference / 4 / 60 ; 
	vel.angular_z  = (float)(-motor_a_rpm + motor_b_rpm - motor_c_rpm + motor_d_rpm) * circumference / 4 / 60 / ((base_width / 2) + (base_long / 2));
	
	return vel;
}
