#include <timing.h>
#include "ros_main.h"
#include "dc_motor.h"
#include "stdbool.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim15;

#define MOTORPLUS_PORT_fr GPIOD
#define MOTORPLUS_PIN_fr GPIO_PIN_8
#define MOTORMINUS_PORT_fr GPIOD
#define MOTORMINUS_PIN_fr GPIO_PIN_14

#define MOTORPLUS_PORT_fl GPIOB
#define MOTORPLUS_PIN_fl GPIO_PIN_12
#define MOTORMINUS_PORT_fl GPIOB
#define MOTORMINUS_PIN_fl GPIO_PIN_13

#define MOTORPLUS_PORT_br GPIOE
#define MOTORPLUS_PIN_br GPIO_PIN_2
#define MOTORMINUS_PORT_br GPIOE
#define MOTORMINUS_PIN_br GPIO_PIN_3

#define MOTORPLUS_PORT_bl GPIOE
#define MOTORPLUS_PIN_bl GPIO_PIN_4
#define MOTORMINUS_PORT_bl GPIOC
#define MOTORMINUS_PIN_bl GPIO_PIN_13

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

#define DIR_PORT_4 GPIOE
#define DIR_PIN_4 GPIO_PIN_8m
#define STEP_PORT_4 GPIOE
#define STEP_PIN_4 GPIO_PIN_9

#define true 1
#define false 0

void motor_standard(void);
void motor_matlab(int fr, int fl, int br, int bl);
void motor_debug(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM13) {

	/* ROS publish */
		static int ms=0;
		ms++;
		if(ms%10==0) ROS::pub_car_vel();

	/* STM control */
//		motor_matlab(true, false, false, false);
		motor_standard();
	}
}


void motor_standard(void){
	/*enc 1*/
		fr.CountNow = __HAL_TIM_GetCounter(&htim2);
		fr.PIDControl_manual();
		__HAL_TIM_SetCounter(&htim2,0);

		if (fr.PID >= 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fr, MOTORPLUS_PIN_fr, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fr, MOTORMINUS_PIN_fr, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fr, MOTORPLUS_PIN_fr, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fr, MOTORMINUS_PIN_fr, GPIO_PIN_SET);
		}

		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, abs((int)fr.PID)*4200);

	/*enc 2*/
		fl.CountNow = __HAL_TIM_GetCounter(&htim5);
		fl.PIDControl_manual();
		__HAL_TIM_SetCounter(&htim5,0);

		if (fl.PID < 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fl, MOTORPLUS_PIN_fl, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fl, MOTORMINUS_PIN_fl, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fl, MOTORPLUS_PIN_fl, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fl, MOTORMINUS_PIN_fl, GPIO_PIN_SET);
		}

		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, abs((int)fl.PID)*4200);

	/*enc 3*/
		br.CountNow = __HAL_TIM_GetCounter(&htim3);
		br.PIDControl_manual();
		__HAL_TIM_SetCounter(&htim3,0);

		if (br.PID >= 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_br, MOTORPLUS_PIN_br, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_br, MOTORMINUS_PIN_br, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_br, MOTORPLUS_PIN_br, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_br, MOTORMINUS_PIN_br, GPIO_PIN_SET);
		}
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, abs((int)br.PID)*4200);

	/*enc 4*/
		bl.CountNow = __HAL_TIM_GetCounter(&htim4);
		bl.PIDControl_manual();
		__HAL_TIM_SetCounter(&htim4,0);

		if (bl.PID >= 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_bl, MOTORPLUS_PIN_bl, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_bl, MOTORMINUS_PIN_bl, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_bl, MOTORPLUS_PIN_bl, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_bl, MOTORMINUS_PIN_bl, GPIO_PIN_SET);
		}
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2,abs((int)bl.PID)*4200);

}

void motor_matlab(int a, int b, int c, int d){
	static int array_count=0;

/*enc 1*/
	fr.CountNow = __HAL_TIM_GetCounter(&htim2);
	__HAL_TIM_SetCounter(&htim2,0);

	fr_array[array_count]=fr.PIDControl_manual();
	if(array_count>4000) array_count=4000;

	HAL_GPIO_WritePin(MOTORPLUS_PORT_fr, MOTORPLUS_PIN_fr, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTORMINUS_PORT_fr, MOTORMINUS_PIN_fr, GPIO_PIN_RESET);

	if(a) __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 4200);
	else __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);


/*enc 2*/
	fl.CountNow = __HAL_TIM_GetCounter(&htim5);
	__HAL_TIM_SetCounter(&htim5,0);

	fl_array[array_count]=fl.PIDControl_manual();
	if(array_count>4000) array_count=4000;

	HAL_GPIO_WritePin(MOTORPLUS_PORT_fl, MOTORPLUS_PIN_fl, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORMINUS_PORT_fl, MOTORMINUS_PIN_fl, GPIO_PIN_SET);

	if(b) __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 4200);
	else __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);


/*enc 3*/
	br.CountNow = __HAL_TIM_GetCounter(&htim3);
	__HAL_TIM_SetCounter(&htim3,0);

	br_array[array_count]=br.PIDControl_manual();
	if(array_count>4000) array_count=4000;

	HAL_GPIO_WritePin(MOTORPLUS_PORT_br, MOTORPLUS_PIN_br, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTORMINUS_PORT_br, MOTORMINUS_PIN_br, GPIO_PIN_RESET);

	if(c) __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 4200);
	else __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 0);


/*enc 4*/
	bl.CountNow = __HAL_TIM_GetCounter(&htim4);
	__HAL_TIM_SetCounter(&htim4,0);

	bl_array[array_count]=bl.PIDControl_manual();
	if(array_count>4000) array_count=4000;

	HAL_GPIO_WritePin(MOTORPLUS_PORT_bl, MOTORPLUS_PIN_bl, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORMINUS_PORT_bl, MOTORMINUS_PIN_bl, GPIO_PIN_SET);

	if(d) __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 4200);
	else __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);

	array_count++;
}
