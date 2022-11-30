#include "ros_main.h"
#include "mecanum.h"
#include "intake.h"
#include "microswitch.h"
#include "reset.h"
#include "scara.h"
#include "intake.h"
#include "STM32Hardware.h"


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
void ROS::scara_callback(const geometry_msgs::Point &msgs){
	static double x_before;
	static double y_before;
	static double z_before;

	if(x_before != msgs.x || y_before != msgs.y || z_before != msgs.z){
		sc.x = msgs.x;
		sc.y = msgs.y;
		sc.flag = msgs.z;
		sc.run();
	}

	x_before = msgs.x;
	y_before = msgs.y;
	z_before = msgs.z;
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
    nh.subscribe(mecanum_sub);
    nh.subscribe(intake_sub);
    nh.subscribe(scara_sub);
}

void ROS::loop(void){
	nh.spinOnce();

	static bool scara_valve_close = true;
	if(scara_valve_close) sc.run();
	scara_valve_close = false;
}


/* UART Communication */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->flush();
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	if(huart == &huart1){
		HAL_UART_DeInit(&huart1);
		MX_USART1_UART_Init();
		nh.getHardware()->init();
	}
}

