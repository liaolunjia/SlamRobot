#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"

#define PI      3.1415926

//速度
#define MAX_RPM         366 //motor's maximum RPM

//PID参数
#define K_P    0.2 // P constant
#define K_I    0.2 // I constant
#define K_D    0.2 // D constant

//轮子
#define WHEEL_DIAMETER  0.0762 //车轮直径
#define LR_WHEELS_DISTANCE  0.28 //左右两轮间距
#define FR_WHEELS_DISTANCE  0.23 //前后两轮间距
#define COUNTS_PER_REV  19100  //减速比20，单圈955

/** Motor Config **/ 
#define MOTORn						4

typedef enum {
	MOTORA = 0, //A轮  前左 
	MOTORB = 1, //B轮  前右 
	MOTORC = 2, //C轮  后左 
	MOTORD = 3	//D轮  后左 
}Motor_TypeDef; 


#endif // _CONFIG_H_