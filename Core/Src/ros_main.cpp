#include "ros_main.h"
#include "mecanum.h"
#include "intake.h"
#include "microswitch.h"
#include "reset.h"
#include "scara.h"
#include "intake.h"

ros::NodeHandle nh;

geometry_msgs::Point microswitch;
geometry_msgs::Point car_speed;
std_msgs::Int64 reset;
std_msgs::Float64 scaraflag;

ros::Subscriber<geometry_msgs::Point> mecanum_sub("mecanum_toSTM", ROS::mecanum_callback);
ros::Subscriber<geometry_msgs::Point> intake_sub("intake_toSTM", ROS::intake_callback);
ros::Subscriber<geometry_msgs::Point> scara_sub("scara_toSTM", ROS::scara_callback);

ros::Publisher mecanum_pub("mecanum_fromSTM", &car_speed);
ros::Publisher reset_pub("reset_fromSTM", &reset);
//ros::Publisher micro_pub("microswitch_fromSTM", &microswitch);
ros::Publisher scara_pub("scaraflag_fromSTM", &scaraflag);

/** RESET **/
void ROS::pub_reset(void){
	MYRESET::receive();
	reset.data = MYRESET::state;
	reset_pub.publish(&reset);
}


/** SCARA **/
void ROS::scara_callback(const geometry_msgs::Point &msg){
	sc.x = msg.x;
	sc.y = msg.y;
	sc.flag = msg.z;
	sc.run();
}

void ROS::pub_scaraflag(void){
	scaraflag.data = sc.flag;
	scara_pub.publish(&scaraflag);
}

/** INTAKE **/
void ROS::intake_callback(const geometry_msgs::Point &msg){
	INTAKE::tilt = msg.x;
	INTAKE::stretch = msg.y;
	INTAKE::suck = msg.z;
	INTAKE::run();
}


/** MICROSWITCH **/
//void ROS::pub_micro(void){
//	microswitch.x = MICROSWITCH::touch_a;
//	microswitch.y = MICROSWITCH::touch_b;
//	microswitch.z = MICROSWITCH::touch_c;
//	micro_pub.publish(&microswitch);
//}



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

    nh.advertise(mecanum_pub);
    nh.advertise(reset_pub);
    nh.advertise(scara_pub);
//    nh.advertise(micro_pub);
    nh.subscribe(mecanum_sub);
    nh.subscribe(intake_sub);
    nh.subscribe(scara_sub);
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
