#include "mecanum.h"
#include "dc_motor.h"

Mecanum mecanum;

Mecanum::Mecanum(void){
	DC_motor_init();
}

// calculate wheel (-> PID) -> calculate car -> pub
void Mecanum::run(void){
	tf2_wheel_speed();
	tf2_car_speed();
}

// alter wheel speed
void Mecanum::tf2_wheel_speed(void){
	fr.rps_goal = (CAR_Goal.Vy - CAR_Goal.Vx + CAR_Goal.Omega*(a+b) )/radius;
	fl.rps_goal = (CAR_Goal.Vy + CAR_Goal.Vx - CAR_Goal.Omega*(a+b) )/radius;
	bl.rps_goal = (CAR_Goal.Vy - CAR_Goal.Vx - CAR_Goal.Omega*(a+b) )/radius;
	br.rps_goal = (CAR_Goal.Vy + CAR_Goal.Vx + CAR_Goal.Omega*(a+b) )/radius;
}


// give current car speed
void Mecanum::tf2_car_speed(void){
	CAR_Now.Vx = (1/4)*(fl.rps_now + fr.rps_now + bl.rps_now + br.rps_now);
	CAR_Now.Vy = (1/4)*(-fl.rps_now + fr.rps_now + bl.rps_now - br.rps_now);
	CAR_Now.Omega = (1/4)*(1/(a+b))*(-fl.rps_now + fr.rps_now - bl.rps_now + br.rps_now);
}
