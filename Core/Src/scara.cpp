#include "scara.h"

SCARA sc;

void SCARA::run(){
	//'update' is used by ST
	if (update == 1){
		x = ST_test_x;
		y = ST_test_y;
		flag = ST_test_flag;
		update = 0;
	}
	while(flag != 0 || step_3 != 0){
		phi = count_phi(x,y);
		at = count_atan2(x,y);
		if (count_atan2(x,y) < 0)at += 360;
		if (at + phi <= 230){
			angle_goal_1 = at + phi;
			angle_goal_2 = -count_theta2(x,y);
		}
		else if(at + phi > 230){
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
				timer_delay(0.3);
				__HAL_TIM_SET_COMPARE(&htim23, TIM_CHANNEL_1, pulse_now);
			}
			while (pulse_now > pulse_goal){
				pulse_now --;
				timer_delay(0.3);
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

			if (state == 1)step_1 *= 1.1; //undetermined
			if (state == 2)step_1 *= 1.1; //undetermined
			input_check = 1;
			angle_now_1 = angle_goal_1;
		}

		if (angle_goal_2 != angle_now_2) {
			step_2 = (angle_goal_2 - angle_now_2)*8 / 0.9;

			if (angle_now_2 >= 180 && angle_goal_2 < 180){
				step_2 += 3200;
			} else if (angle_now_2 < 180 && angle_goal_2 >= 180){
			   step_2 -= 3200;
			}

			if (step_2 >= 0) {
				HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_SET);
			} else if (step_2 < 0) {
				step_2 = -step_2;
				HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_RESET);
			}

			if (state == 1)step_2 *= 1.05; //undetermined
			if (state == 2)step_2 *= 1.1; //undetermined
			input_check = 1;
			angle_now_2 = angle_goal_2;
		}


		if (high_goal != high_now) {
			step_3 = (high_goal - high_now)*200 *8 / 6;
			a = 0;
			if (step_3 >= 0) {
				HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_SET); a=999;
			} else if (step_3 < 0) {
				step_3 = -step_3;
				HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_RESET); a=222;
			}
			input_check = 1;
			high_now = high_goal;
		}

		if (step_1 < 1 && step_1 > 0)step_1 = 1;
		if (step_2 < 1 && step_2 > 0)step_2 = 1;
		if (step_3 < 1 && step_3 > 0)step_3 = 1;

		if (valve_switch == 1){
			timer_delay(2);
			valve_switch = 0;
		}

		if (step_1 == 0 && step_2 == 0 && step_3 == 0 ){
			if (flag == 1){
				step_1 = 60;
				HAL_GPIO_WritePin(DIR_PORT_1, DIR_PIN_1, GPIO_PIN_SET);
				step_2 = 30;
				HAL_GPIO_WritePin(DIR_PORT_2, DIR_PIN_2, GPIO_PIN_RESET);
				step_3 = 2000;
				HAL_GPIO_WritePin(DIR_PORT_3, DIR_PIN_3, GPIO_PIN_SET);
				flag = 6;
			}
			else if (flag == 2){
				flag = 6;
			}
			else if (flag == 3){
				air_pressure = 1, valve_switch = 0;

//				if (high_state == 0){
//					high_goal = -93;
//					high_state ++;
//				}
//				else if (high_state == 1){
//					timer_delay(1);
//					high_goal = 0;
//					high_state ++;
//				}
//				else if(high_state == 2){
//					if (state == 0)servo_angle = 20,state++;
//					else if (state == 1)servo_angle = 270, state++;
//					else if (state == 2)servo_angle = 145;
//					high_state ++;
//				}
//				else if (high_state == 3 && pulse_now == pulse_goal){
//					high_state = 0;
//					flag = 6;
//				}
				switch(high_state){
					case 0:
						if (state == 0)servo_angle = 20,state++;
						else if (state == 1)servo_angle = 270, state++;
						else if (state == 2)servo_angle = 145;
						high_state = 1;
						break;

					case 1:
						high_goal = -93;
						high_state = 2;
						break;

					case 2:
						timer_delay(1);
						high_goal = 0;
						high_state = 3;
						break;

					case 3:
						if(pulse_now == pulse_goal){
							high_state = 0;
							flag = 6;
						}
						break;
				}
			}else if (step_1 == 0 && step_2 == 0 && flag == 4){
				servo_angle = 145;
				air_pressure = 0;
				valve_switch = 1;
				state = 0;
				flag = 6;
			}else if (step_1 == 0 && step_2 == 0 && step_3 ==0 && flag == 5){
				high_goal = -10;
				flag = 6;
			}else if (step_3 == 0 && flag == 6){
				flag =0 ;
			}
		}
	}
}

void SCARA::timer_delay(int sec){
	SCARA::timer_flag = true;
	while(SCARA::timer_count <= sec*1000);
	SCARA::timer_count =0;
	SCARA::timer_flag = false;
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

