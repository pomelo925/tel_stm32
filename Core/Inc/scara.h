#ifndef _SCARA_H_
#define _SCARA_H_


typedef struct{
	// sub from ROS //
	double Px;
	double Py;
	double Pz;

	// pub to ROS //
	bool is_finished = false;
} ARM_INFO;

class SCARA{
public:
	ARM_INFO ARM_Goal, ARM_now;
	void run();

private:
	void tf2_arm_angle(void);

};

extern SCARA scara;

#endif
