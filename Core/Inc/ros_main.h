#ifndef _ROS_MAIN_H_
#define _ROS_MAIN_H_

#include "ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Int64.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

namespace ROS{
	void setup(void);
	void loop(void);

	/* STM callback */
	void mecanum_callback(const geometry_msgs::Point &msg);
	void intake_callback(const geometry_msgs::Point &msg);
	void relay_callback(const std_msgs::Int64 &msg);

	/* STM publish */
	void pub_car_vel(void);
	void pub_reset(void);
	void pub_micro(void);
}


#endif
