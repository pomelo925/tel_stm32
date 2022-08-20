#ifndef _ROS_MAIN_H_
#define _ROS_MAIN_H_

#include "ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Bool.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

namespace ROS{
	void setup(void);
	void loop(void);

	void mecanum_callback(const geometry_msgs::Point &msg);
	void scara_callback(const geometry_msgs::Point &nsgs);

	void pub_car_vel(void);
}


#endif