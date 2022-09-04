#include "ros_main.h"
#include "mecanum.h"
#include "scara.h"

ros::NodeHandle nh;

geometry_msgs::Point car_speed;

ros::Subscriber<geometry_msgs::Point> mecanum_sub("mecanum_toSTM", ROS::mecanum_callback);
ros::Subscriber<geometry_msgs::Point> scara_sub("scara_toSTM", ROS::scara_callback);

ros::Publisher mecanum_pub("mecanum_fromSTM", &car_speed);
//ros::Publisher scara_pub("scara_fromSTM", &scara_state);

void ROS::scara_callback(const geometry_msgs::Point &msgs){
	scara.ARM_Goal.Px = msgs.x;
	scara.ARM_Goal.Py = msgs.y;
	scara.ARM_Goal.Pz = msgs.z;
	scara.run();
}

void ROS::mecanum_callback(const geometry_msgs::Point &msgs){
	mecanum.CAR_Goal.Vx = msgs.x;
	mecanum.CAR_Goal.Vy = msgs.y;
	mecanum.CAR_Goal.Omega = msgs.z;
	mecanum.run();
}

// void ROS::pub_car_vel(void){
// 	car_speed.x = mecanum.CAR_Now.Vx;
// 	car_speed.y = mecanum.CAR_Now.Vy;
// 	car_speed.z = mecanum.CAR_Now.Omega;
// 	mecanum_pub.publish(&car_speed);
// }


void ROS::setup(void){
	nh.initNode();

    nh.subscribe(mecanum_sub);

//    nh.advertise(mecanum_pub);
}

void ROS::loop(void){
	nh.spinOnce();
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->reset_rbuf();
}
