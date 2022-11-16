#ifndef _RESET_H_
#define _RESET_H_

/* part */
#define FIRST_PART_PORT GPIOF
#define FIRST_PART_PIN GPIO_PIN_3
#define SECOND_PART_PORT GPIOC
#define SECOND_PART_PIN GPIO_PIN_0
#define THIRD_PART_PORT GPIOC
#define THIRD_PART_PIN GPIO_PIN_1

namespace RESET{
	double state_reset=0;

	void receive(void);
}


#endif
