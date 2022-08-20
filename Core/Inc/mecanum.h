#ifndef _MECANUM_H_
#define _MECANUM_H_

typedef struct{
	double Vx=0;
	double Vy=0;
	double Omega=0;
} CAR_INFO;

class Mecanum{
public:
	Mecanum(void);
	CAR_INFO CAR_Goal, CAR_Now;

	void run(void);

private:
	/* kinectics model argumen(CM) */
	double a=11.5;
	double b=8.4;
	double radius=7.321/2;

	void tf2_wheel_speed(void);
	void tf2_car_speed(void);
	void set_Vgoal(void);
};

extern Mecanum mecanum;

#endif  //_MECANUM_H_
