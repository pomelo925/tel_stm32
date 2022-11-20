#include "scara.h"

SCARA sc;

void SCARA::trinary(double function, GPIO_TypeDef* a_port,
		uint16_t a_pin, GPIO_TypeDef* b_port, uint16_t b_pin){ \
	if (function == 1) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_SET);
	}
	else if (function == 0) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_RESET);
	}
	else if (function == -1) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_RESET);
	}
}


void SCARA::run(){
	/* relay */
	sc.trinary(relay, VALVE_PORT, VALVE_PIN, AIR_PORT, AIR_PIN);

	/* arm */
	sc.seize();
}

void SCARA::seize(){
	//'update' is used by ST
	if (update == 1){
		x = ST_test_x;
		y = ST_test_y;
		flag = ST_test_flag;
		update = 0;
	}

	phi = count_phi(x,y);
	at = count_atan2(x,y);
	if (count_atan2(x,y) < 0)at += 360;
	if (at + phi <= 250){
		angle_goal_1 = at + phi;
		angle_goal_2 = -count_theta2(x,y);
	}
	else if(at + phi > 250){
		angle_goal_1 = at - phi;
		angle_goal_2 = count_theta2(x,y);
	}

	 if (air_pressure == 1)HAL_GPIO_WritePin(AIR_PORT, AIR_PIN, GPIO_PIN_RESET);
	 else if (air_pressure == 0)HAL_GPIO_WritePin(AIR_PORT, AIR_PIN, GPIO_PIN_SET);

	 if (valve_switch == 1)HAL_GPIO_WritePin(VALVE_PORT, VALVE_PIN, GPIO_PIN_RESET);
	 else if (valve_switch == 0)HAL_GPIO_WritePin(VALVE_PORT, VALVE_PIN, GPIO_PIN_SET);

	 pulse_goal = 600 + 10 * servo_angle;
	 if (servo_angle == 145)__HAL_TIM_SET_COMPARE(&htim23, TIM_CHANNEL_1, pulse_now);
	 if (pulse_now != pulse_goal){
	  while (pulse_now < pulse_goal){
	   pulse_now ++;
	   HAL_Delay(0.3);
	   __HAL_TIM_SET_COMPARE(&htim23, TIM_CHANNEL_1, pulse_now);
	  }
	  while (pulse_now > pulse_goal){
	   pulse_now --;
	   HAL_Delay(0.3);
	   __HAL_TIM_SET_COMPARE(&htim23, TIM_CHANNEL_1, pulse_now);
	  }
	  input_check = 1;
	  pulse_now = pulse_goal;
	 }


	 if (angle_goal_1 != angle_now_1) {

	  step_1 = (double)(angle_goal_1 - angle_now_1)*4 *8 / 0.9;

	  if (step_1 >= 0) {
	   HAL_GPIO_WritePin(DIR_PORT_1, DIR_PIN_1, GPIO_PIN_SET);
	  }else if (step_1 < 0) {
	   step_1 = -step_1;
	   HAL_GPIO_WritePin(DIR_PORT_1, DIR_PIN_1, GPIO_PIN_RESET);
	  }
	  if (state == 1)step_1 *= 1.02; //undetermined
	  if (state == 2)step_1 *= 1.05; //undetermined
	  input_check = 1;
	  angle_now_1 = angle_goal_1;
	 }

	 if (angle_goal_2 != angle_now_2) {

	  step_2 = (angle_goal_2 - angle_now_2)*8 / 0.9;

	  if (angle_now_2 >= 180 && angle_goal_2 < 180){
	   step_2 += 3200;
	  }else if (angle_now_2 < 180 && angle_goal_2 >= 180){
	   step_2 -= 3200;
	  }

	  if (step_2 >= 0) {
	   HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_SET);
	  }else if (step_2 < 0) {
	   step_2 = -step_2;
	   HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_RESET);
	  }
	  if (state == 1)step_2 *= 1.02; //undetermined
	  if (state == 2)step_2 *= 1.05; //undetermined
	  input_check = 1;
	  angle_now_2 = angle_goal_2;
	 }

	 if (high_goal != high_now) {

	  step_3 = (high_goal - high_now)*200 *8 / 6;

	  if (step_3 >= 0) {
	   HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_SET);
	  }else if (step_3 < 0) {
	   step_3 = -step_3;
	   HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_RESET);
	  }
	  input_check = 1;
	  high_now = high_goal;
	 }

	 if (step_1 < 1 && step_1 > 0)step_1 = 1;
	 if (step_2 < 1 && step_2 > 0)step_2 = 1;
	 if (step_3 < 1 && step_3 > 0)step_3 = 1;


	 if (x == 0 && y == -50 && flag == 1){
	  step_1 = 120;
	  HAL_GPIO_WritePin(DIR_PORT_1, DIR_PIN_1, GPIO_PIN_SET);
	  step_2 = 30;
	  HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_RESET);
	  step_3 = 2000;
	  HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_SET);
	  flag = 5;
	 }
	 if (valve_switch == 1){
	  HAL_Delay(2000);
	  valve_switch = 0;
	 }


	 if (step_1 == 0 && step_2 == 0 && step_3 == 0 && input_check == 1){

	  if (flag == 2){
	   flag = 5;
	  }
	  else if (flag == 3){
	   air_pressure = 1, valve_switch = 0;
	   if (high_state == 0){
	    if (state == 0)servo_angle = 20,state++;
	    else if (state == 1)servo_angle = 270, state++;
	    else if (state == 2)servo_angle = 145;
	    high_state = 1;
	   }
	   else if (high_state == 1){
	    high_goal = -89;
	    high_state = 2;
	   }
	   else if (high_state == 2){
	    HAL_Delay(2000);
	    high_goal = 0;
	    high_state = 3;
	   }
	 else if(high_state == 3 && pulse_now == pulse_goal){
	    high_state = 0;
	    flag = 5;
	   }
	  }
	 else if (step_1 == 0 && step_2 == 0 && flag == 4){
	   air_pressure = 0;
	   valve_switch = 1;
	   state = 0;
	   flag = 5;
	  }
	  input_check = 0;
	 }


	 if (step_1 == 0 && step_2 == 0 && step_3 == 0 && flag == 5){
		 flag = 0;
	 }
}

double SCARA::count_atan2(double x, double y)
{
 double atan2;
 double temp = y/x;
 if(x > 0){
   atan2 = (atan(temp)*180)/PI;
 }
    else if(y >= 0 && x < 0){
        atan2 = (atan(temp)*180)/PI + 180;
    }
    else if(y < 0 && x < 0){
        atan2 = (atan(temp)*180/PI - 180);
    }
    else if(y > 0 && x == 0){
        atan2 = 180/2;
    }
    else if(y < 0 && x == 0){
        atan2 = -180/2;
    }
 return atan2;
}

double SCARA::count_theta2(double x, double y)
{
 double theta2;
 double temp;
 temp = (double)(pow(x,2) + pow(y,2) - pow(length1,2) - pow(length2,2));
 temp /= (double)(2*length1*length2);
 theta2 = (acos(temp)*180)/PI;
 return theta2;
}

double SCARA::count_phi(double x, double y)
{
 double phi;
 double temp = pow(length2,2) - pow(length1,2) - pow(x,2) - pow(y,2);
 temp /= (double)(-2*length1*sqrt(pow(x,2)+pow(y,2)));
 phi = (acos(temp)*180)/PI;
 return phi;
}

