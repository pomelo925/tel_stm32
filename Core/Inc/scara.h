#ifndef _SCARA_H_
#define _SCARA_H_

/* RELAY */
#define RELAY_A_PORT GPIOA
#define RELAY_A_PIN GPIO_PIN_4
#define RELAY_B_PORT GPIOA
#define RELAY_B_PIN GPIO_PIN_5

namespace SCARA{
	double relay;
	void trinary(double function, char a_port, char a_pin, char b_port, char b_pin);
	void run();
}

#endif
