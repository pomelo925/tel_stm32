#include "dc_motor.h"
#include "stm32h7xx_hal.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim23;
extern TIM_HandleTypeDef htim24;

/** PIDControl **/
DC_motor fr(1000,0.5,0, 0.001,512,20.8);
DC_motor fl(1000,0.5,0, 0.001,512,20.8);
DC_motor br(1000,0.5,0, 0.001,512,13.2);
DC_motor bl(1000,0.5,0, 0.001,512,20.8);

/** Manual **/
//DC_motor fr(0.754, 52.5, 0, 0.001, 42600, 200);
//DC_motor fl(5.5, 85, 0, 0.001, 43193, 200);
//DC_motor br(148.3, 2813.3, 0.537, 0.001, 26734, 200);
//DC_motor bl(0, 0, 0, 0.001, 41296, 200);


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
	HAL_TIM_Base_Start_IT(&htim24);
}

DC_motor::DC_motor(double p, double i, double d, double time, double res, double ratio){
	this->kp = p;
	this->ki = i;
	this->kd = d;
	this->time = time;
	this->res_encoder = res;
	this->sr_ratio = ratio;
}

//DC_motor::DC_motor(double p, double i, double d, double time, double cnt_round, double limit){
//	this->p = p;
//	this->i = i;
//	this->d = d;
//	this->time = time;
//	this->cnt_round = cnt_round;
//	this->I_limit=limit;
//}

//double DC_motor::PIDControl_manual(void){
//	temp = error;
//	rps_now = (double) CountNow / cnt_round / time;
//
//	error = rps_goal - rps_now;
//	P = p * error;
//	sum = i * error * time;
//	I = I + sum;
//	if (rps_now == 0) {
//		I = 0;
//	}
//	if (I >= I_limit) {
//		I = I_limit;
//	}
//	if (I < -I_limit) {
//		I = -I_limit;
//	}
//	D = d * (error - temp) / time;
//	PID = P + I + D;
//
//	if(PID>1) PID=1;
//	if(PID<-1) PID=-1;
//
//	return rps_now;
//}

void DC_motor::PIDControl(void){
	rps_now = (double) CountNow / 4 / res_encoder / sr_ratio / time;

	error = rps_goal - rps_now;
	error_total += error;
	PWM = error*kp + error_total*ki + error_last*kd;
	error_last = error;
}


