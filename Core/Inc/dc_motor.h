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
		unsigned short CountNow;
		double I_limit;
		double temp;
		int pid_check=0;

		DC_motor(double p, double i, double d, double time, double res, double ratio, double limit);
		void PIDControl();
};

extern DC_motor fr;
extern DC_motor fl;
extern DC_motor br;
extern DC_motor bl;

void DC_motor_init();


#endif
