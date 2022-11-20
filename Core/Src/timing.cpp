#include "timing.h"
#include "ros_main.h"
#include "dc_motor.h"
#include "reset.h"
#include "scara.h"
#include "microswitch.h"

int axx=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/** SCARA **/
	if (htim->Instance == TIM7) {
		/*stepper 2*/
		if (sc.temp_2 == 1) {
			HAL_GPIO_WritePin(STEP_PORT_2, STEP_PIN_2, GPIO_PIN_SET);
			sc.temp_2 = 0;
		}
		else if (sc.step_2 >= 1) {
			HAL_GPIO_WritePin(STEP_PORT_2, STEP_PIN_2, GPIO_PIN_RESET);
			sc.temp_2 = 1;
			sc.step_2 = sc.step_2 - 1;
		}
	}

	if (htim->Instance == TIM8) {
	  /*stepper 1*/
		if (sc.temp_1 == 1) {
			HAL_GPIO_WritePin(STEP_PORT_1, STEP_PIN_1, GPIO_PIN_SET);
			sc.temp_1 = 0;
		}
		else if (sc.step_1 >= 1) {
			HAL_GPIO_WritePin(STEP_PORT_1, STEP_PIN_1, GPIO_PIN_RESET);
			sc.temp_1 = 1;
			sc.step_1 = sc.step_1 - 1;
		}
	}

	if (htim->Instance == TIM14) {
		/*stepper 3*/
		if (sc.temp_3 == 1) {
			HAL_GPIO_WritePin(STEP_PORT_3, STEP_PIN_3, GPIO_PIN_SET);
			sc.temp_3 = 0;
		}
		else if (sc.step_3 >= 1) {
			HAL_GPIO_WritePin(STEP_PORT_3, STEP_PIN_3, GPIO_PIN_RESET);
			sc.temp_3 = 1;
			sc.step_3 = sc.step_3 - 1;
		}
	}
	/**  **/


	if (htim->Instance == TIM13) {
	/* ROS publish */
		static int ms=0;
		if(ms%10==0){
			ROS::pub_car_vel();
			ROS::pub_reset();
		}
		ms++;

	/* PID Control */
		motor_standard();
		axx++;
	}


	/** Intake **/
	if (htim->Instance == TIM24){
		/* microswitch */
		if (HAL_GPIO_ReadPin(TOUCH_A_PORT, TOUCH_A_PIN) == 0) {
			MICROSWITCH::touch_a = 1;
		} else MICROSWITCH::touch_a = 0;

		if (HAL_GPIO_ReadPin(TOUCH_B_PORT, TOUCH_B_PIN) == 0) {
			MICROSWITCH::touch_b = 1;
		} else MICROSWITCH::touch_b = 0;

		if (HAL_GPIO_ReadPin(TOUCH_C_PORT, TOUCH_C_PIN) == 0) {
			MICROSWITCH::touch_c = 1;
		} else MICROSWITCH::touch_c = 0;
	}
}


void motor_standard(void){
	/*enc 1*/
		fr.CountNow = __HAL_TIM_GetCounter(&htim2);
		fr.PIDControl();
		__HAL_TIM_SetCounter(&htim2,0);

		if (fr.PWM < 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fr, MOTORPLUS_PIN_fr, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fr, MOTORMINUS_PIN_fr, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fr, MOTORPLUS_PIN_fr, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fr, MOTORMINUS_PIN_fr, GPIO_PIN_SET);
		}

		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, fabs(fr.PWM));

	/*enc 2*/
		fl.CountNow = __HAL_TIM_GetCounter(&htim5);
		fl.PIDControl();
		__HAL_TIM_SetCounter(&htim5,0);

		if (fl.PWM > 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fl, MOTORPLUS_PIN_fl, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fl, MOTORMINUS_PIN_fl, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_fl, MOTORPLUS_PIN_fl, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_fl, MOTORMINUS_PIN_fl, GPIO_PIN_SET);
		}

		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, fabs(fl.PWM));

	/*enc 3*/
		br.CountNow = __HAL_TIM_GetCounter(&htim3);
		br.PIDControl();
		__HAL_TIM_SetCounter(&htim3,0);

		if (br.PWM > 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_br, MOTORPLUS_PIN_br, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_br, MOTORMINUS_PIN_br, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_br, MOTORPLUS_PIN_br, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_br, MOTORMINUS_PIN_br, GPIO_PIN_SET);
		}
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, fabs(br.PWM));

	/*enc 4*/
		bl.CountNow = __HAL_TIM_GetCounter(&htim4);
		bl.PIDControl();
		__HAL_TIM_SetCounter(&htim4,0);

		if (bl.PWM < 0) {
			HAL_GPIO_WritePin(MOTORPLUS_PORT_bl, MOTORPLUS_PIN_bl, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_bl, MOTORMINUS_PIN_bl, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(MOTORPLUS_PORT_bl, MOTORPLUS_PIN_bl, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MOTORMINUS_PORT_bl, MOTORMINUS_PIN_bl, GPIO_PIN_SET);
		}
		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, fabs(bl.PWM));

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
