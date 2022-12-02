#ifndef _SCARA_H_
#define _SCARA_H_

#include "stm32h7xx_hal.h"
#include "timing.h"

/* SCARA */
#define PI 3.1415926535897932384
#define length1 190 //189.75
#define length2 140 //136.855

#define DIR_PORT_1 GPIOC
#define DIR_PIN_1 GPIO_PIN_5
#define STEP_PORT_1 GPIOF
#define STEP_PIN_1 GPIO_PIN_9

#define DIR_PORT_2 GPIOF
#define DIR_PIN_2 GPIO_PIN_11
#define STEP_PORT_2 GPIOF
#define STEP_PIN_2 GPIO_PIN_8

#define DIR_PORT_3 GPIOF
#define DIR_PIN_3 GPIO_PIN_15
#define STEP_PORT_3 GPIOB
#define STEP_PIN_3 GPIO_PIN_9

#define VALVE_PORT GPIOA
#define VALVE_PIN GPIO_PIN_4
#define AIR_PORT GPIOA
#define AIR_PIN GPIO_PIN_5

extern TIM_HandleTypeDef htim23;

struct SCARA{
	bool timer_flag=false;
	int timer_count=0;

	double x = 0, y = -50;
	double phi, at;

	double angle_goal_1 = 270;
	double step_1 = 0;
	double angle_now_1 = 270;
	int temp_1 = 0;

	double angle_goal_2 = -180;
	double step_2 = 0;
	double angle_now_2 = -180;
	int temp_2 = 0;

	double high_goal = 0;
	double step_3 = 0;
	double high_now = 0;
	int temp_3 = 0;
	int high_state = 0;

	double servo_angle = 145;
	double pulse_now = 2050;
	double pulse_goal = 2050;

	double state = 0;  //ROS
	double flag = 1;  //
	int input_check = 0;

	int air_pressure = 0;
	int valve_switch = 0;

	double ST_test_x = 0;
	double ST_test_y = -50;
	int ST_test_flag = 0;
	int update = 0;

	int a =0;

	double relay;

	void run();

	void timer_delay(int sec);
	double count_atan2(double x, double y);
	double count_theta2(double x, double y);
	double count_phi(double x, double y);
};

extern SCARA sc;

#endif
