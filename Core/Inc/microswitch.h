#ifndef _MICROSWITCH_H_
#define _MICROSWITCH_H_

/* TOUCH */
#define TOUCH_A_PORT GPIOG
#define TOUCH_A_PIN GPIO_PIN_6
#define TOUCH_B_PORT GPIOG
#define TOUCH_B_PIN GPIO_PIN_5
#define TOUCH_C_PORT GPIOG
#define TOUCH_C_PIN GPIO_PIN_4

namespace MICROSWITCH{
	void receive(void);
}

#endif
