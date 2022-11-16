#include "scara.h"

namespace SCARA{
	double relay;
}

void SCARA::trinary(double function, GPIO_TypeDef* a_port,
		uint16_t a_pin, GPIO_TypeDef* b_port, uint16_t b_pin){ \
	if (function == 1) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_SET);
	}
	else if (function == 0) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_RESET);
	}
	else if (function == -1) {
		HAL_GPIO_WritePin(a_port, a_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(b_port, b_pin, GPIO_PIN_RESET);
	}
}


void SCARA::run(){
	/* relay */
	SCARA::trinary(relay, RELAY_A_PORT, RELAY_A_PIN, RELAY_B_PORT, RELAY_B_PIN);

	/* arm */

}

