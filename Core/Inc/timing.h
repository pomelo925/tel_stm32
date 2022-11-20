#ifndef _TIMER_ELAPSE_H_
#define _TIMER_ELAPSE_H_

#include "stm32h7xx_hal.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim15;

#define MOTORPLUS_PORT_fr GPIOD
#define MOTORPLUS_PIN_fr GPIO_PIN_8
#define MOTORMINUS_PORT_fr GPIOD
#define MOTORMINUS_PIN_fr GPIO_PIN_14

#define MOTORPLUS_PORT_fl GPIOB
#define MOTORPLUS_PIN_fl GPIO_PIN_12
#define MOTORMINUS_PORT_fl GPIOB
#define MOTORMINUS_PIN_fl GPIO_PIN_13

#define MOTORPLUS_PORT_br GPIOE
#define MOTORPLUS_PIN_br GPIO_PIN_2
#define MOTORMINUS_PORT_br GPIOE
#define MOTORMINUS_PIN_br GPIO_PIN_3

#define MOTORPLUS_PORT_bl GPIOE
#define MOTORPLUS_PIN_bl GPIO_PIN_4
#define MOTORMINUS_PORT_bl GPIOC
#define MOTORMINUS_PIN_bl GPIO_PIN_13

#define DIR_PORT_1 GPIOC
#define DIR_PIN_1 GPIO_PIN_5
#define STEP_PORT_1 GPIOF
#define STEP_PIN_1 GPIO_PIN_9

#define DIR_PORT_2 GPIOF
#define DIR_PIN_2 GPIO_PIN_11
#define STEP_PORT_2 GPIOF
#define STEP_PIN_2 GPIO_PIN_8

#define DIR_PORT_3 GPIOF
#define DIR_PIN_3 GPIO_PIN_15
#define STEP_PORT_3 GPIOB
#define STEP_PIN_3 GPIO_PIN_9

#define DIR_PORT_4 GPIOE
#define DIR_PIN_4 GPIO_PIN_8m
#define STEP_PORT_4 GPIOE
#define STEP_PIN_4 GPIO_PIN_9

#define true 1
#define false 0

void motor_standard(void);
void motor_matlab(int fr, int fl, int br, int bl);
void motor_debug(void);


static double fr_array[5000]={0};
static double fl_array[5000]={0};
static double br_array[5000]={0};
static double bl_array[5000]={0};



#endif
