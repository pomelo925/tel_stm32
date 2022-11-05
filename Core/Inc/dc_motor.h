#ifndef _MOTOR_H_
#define _MOTOR_H_

class DC_motor{
	private:
		double res_encoder;
		double sr_ratio;
		double error;
		double error_total;
		double error_last;
		double cnt_round;
		double time;

	public:
		double rps_goal;
		double rps_now;
		short CountNow;

		double kp;
		double ki;
		double kd;
		double PWM;

		DC_motor(double p, double i, double d, double time, double cnt_round, double limit);
		DC_motor(double p, double i, double d, double time, double res, double ratio, double limit);
		double PIDControl_manual();
		void PIDControl();
};

extern DC_motor fr;
extern DC_motor fl;
extern DC_motor br;
extern DC_motor bl;

void DC_motor_init();


#endif
