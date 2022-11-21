#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "stm32h7xx_hal.h"

/* TILT */
#define TILT_INA_PORT GPIOB
#define TILT_INA_PIN GPIO_PIN_10
#define TILT_INB_PORT GPIOC
#define TILT_INB_PIN GPIO_PIN_4

/* SUCK */
#define SUCK_INA_PORT GPIOA
#define SUCK_INA_PIN GPIO_PIN_6
#define SUCK_INB_PORT GPIOA
#define SUCK_INB_PIN GPIO_PIN_7

/* STRETCH */
#define STRETCH_INA_PORT GPIOB
#define STRETCH_INA_PIN GPIO_PIN_6
#define STRETCH_INB_PORT GPIOB
#define STRETCH_INB_PIN GPIO_PIN_7

namespace INTAKE{
	extern double tilt, stretch, suck;

	void run();
}

#endif
