#ifndef _SCARA_H_
#define _SCARA_H_

#include "stm32h7xx_hal.h"

/* RELAY */
#define RELAY_A_PORT GPIOA
#define RELAY_A_PIN GPIO_PIN_4
#define RELAY_B_PORT GPIOA
#define RELAY_B_PIN GPIO_PIN_5



namespace SCARA{
	extern double relay;
	void trinary(double function, GPIO_TypeDef* a_port, uint16_t a_pin, \
			GPIO_TypeDef* b_port, uint16_t b_pin);
	void run();
}

#endif
