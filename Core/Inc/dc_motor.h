#ifndef _MOTOR_H_
#define _MOTOR_H_

class DC_motor{
	public:
		double p, P;
		double i, I;
		double d, D;
		double PID;
		double rps_goal;
		double rps_now;
		double time;
		double sum;
		double res_encoder;
		double sr_ratio;
		double error;
		short CountNow;
		double I_limit;
		double temp;
		double cnt_round;
		int pid_check=0;

		DC_motor(double p, double i, double d, double time, double cnt_round, double limit);
		DC_motor(double p, double i, double d, double time, double res, double ratio, double limit);
		double PIDControl_manual();
		double PIDControl();

};

extern DC_motor fr;
extern DC_motor fl;
extern DC_motor br;
extern DC_motor bl;

void DC_motor_init();


#endif
