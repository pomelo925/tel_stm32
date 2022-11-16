#ifndef _MICROSWITCH_H_
#define _MICROSWITCH_H_

#include "stm32h7xx_hal.h"

/* TOUCH */
#define TOUCH_A_PORT GPIOG
#define TOUCH_A_PIN GPIO_PIN_6
#define TOUCH_B_PORT GPIOG
#define TOUCH_B_PIN GPIO_PIN_5
#define TOUCH_C_PORT GPIOG
#define TOUCH_C_PIN GPIO_PIN_4

namespace MICROSWITCH{
	extern double touch_a, touch_b, touch_c;

	void receive(void);
}

#endif
