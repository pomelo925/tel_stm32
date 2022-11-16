#ifndef _INTAKE_H_
#define _INTAKE_H_

/* TILT */
#define TILT_INA_PORT GPIOB
#define TILT_INA_PIN GPIO_PIN_6
#define TILT_INB_PORT GPIOF
#define TILT_INB_PIN GPIO_PIN_2

/* SUCK */
#define SUCK_INA_PORT GPIOA
#define SUCK_INA_PIN GPIO_PIN_6
#define SUCK_INB_PORT GPIOA
#define SUCK_INB_PIN GPIO_PIN_7

/* STRETCH */
#define STRETCH_INA_PORT GPIOC
#define STRETCH_INA_PIN GPIO_PIN_4
#define STRETCH_INB_PORT GPIOB
#define STRETCH_INB_PIN GPIO_PIN_7

namespace INATKE{
	double  tilt, stretch, suck;

	void trinary(double function, char a_port, char a_pin, char b_port, char b_pin);
	void run();
}

#endif
