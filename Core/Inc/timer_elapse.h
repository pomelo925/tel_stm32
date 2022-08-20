#ifndef _TIMER_ELAPSE_H_
#define _TIMER_ELAPSE_H_

#include "stm32h7xx_hal.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
