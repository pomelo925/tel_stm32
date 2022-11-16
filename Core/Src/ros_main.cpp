#include "ros_main.h"
#include "mecanum.h"
#include "intake.h"
#include "microswitch.h"

ros::NodeHandle nh;

geometry_msgs::Point microswitch;
geometry_msgs::Point car_speed;
std_msgs::Int64 relay;
std_msgs::Int64 reset;

ros::Subscriber<geometry_msgs::Point> mecanum_sub("mecanum_toSTM", ROS::mecanum_callback);
ros::Subscriber<geometry_msgs::Point> intake_sub("intake_toSTM", ROS::intake_callback);
ros::Subscriber<std_msgs::Int64> relay_sub("relay_toSTM", ROS::relay_callback);

ros::Publisher mecanum_pub("mecanum_fromSTM", &car_speed);
ros::Publisher reset_pub("reset_fromSTM", &reset);
ros::Publisher micro_pub("microswitch_fromSTM", &microswitch);

/** RESET **/
void ROS::pub_reset(void){
	RESET::receive();
	reset.data = RESET::state_reset;
	reset_pub.publish(&reset);
}


/** SCARA **/
void relay_callback(const std_msgs::Int64 &msgs){
	SCARA::relay = msgs.data;
}


/** INTAKE **/
void intake_callback(const geometry_msgs::Point &msgs){
	INTAKE::tilt = msgs.x;
	INTAKE::stretch = msgs.y;
	INTAKE::suck = msgs.z;
	INTAKE::run();
}


/** MICROSWITCH **/
void pub_micro(void){
	miro_pub.publish(&microswithc);
}



/** CHASSIS -- mecanum **/
void ROS::mecanum_callback(const geometry_msgs::Point &msgs){
	mecanum.CAR_Goal.Vx = msgs.x;
	mecanum.CAR_Goal.Vy = msgs.y;
	mecanum.CAR_Goal.Omega = msgs.z;
	mecanum.run();
}

void ROS::pub_car_vel(void){
	car_speed.x = mecanum.CAR_Now.Vx;
 	car_speed.y = mecanum.CAR_Now.Vy;
 	car_speed.z = mecanum.CAR_Now.Omega;
 	mecanum_pub.publish(&car_speed);
}


/** ROS setup and loop **/
void ROS::setup(void){
	nh.initNode();

    nh.subscribe(mecanum_sub);
    nh.advertise(mecanum_pub);
}

void ROS::loop(void){
	nh.spinOnce();
}


/* UART Communication */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->reset_rbuf();
}
