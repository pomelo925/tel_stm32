#include "dc_motor.h"
#include "stm32h7xx_hal.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim15;

/*** Arguments NON-SETUP ***/
DC_motor fr(105,3,0.002,0.001,512,13.2,200);
DC_motor fl(5.2,2,0.001,0.001,512,13.2,200);
DC_motor br(155,2,0.002,0.001,512,13.2,200);
DC_motor bl(155,5,0.006,0.001,512,13.2,200);

void DC_motor_init(){
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim13);
	HAL_TIM_PWM_Start_IT(&htim12, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim15, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim15, TIM_CHANNEL_1);
}

DC_motor::DC_motor(double p, double i, double d, double time, double res, double ratio, double limit){
	this->p = p;
	this->i = i;
	this->d = d;
	this->time = time;
	this->res_encoder = res;
	this->sr_ratio = ratio;
	this->I_limit=limit;
}

void DC_motor::PIDControl(void){

	pid_check++;
	temp = error;
	rps_now = (double) CountNow / 4 / res_encoder / sr_ratio / time;
	if(rps_now>10||rps_now<-10){
		rps_now=0;
		I=0;
	}
	error = rps_goal - rps_now;
	P = p * error;
	sum = i * error * time;
	I = I + sum;
	if (rps_now == 0) {
		I = 0;
	}
	if (I >= I_limit) {
		I = I_limit;
	}
	if (I < -I_limit) {
		I = -I_limit;
	}
	D = d * (error - temp) / time;
	PID = P + I + D;


}



