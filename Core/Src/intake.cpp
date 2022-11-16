#include "intake.h"

void INTAKE::trinary(double function, char a_port, char a_pin, char b_port, char b_pin){
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

void INTAKE::run(void){
	INTAKE::trinary(INTAKE::tilt, TILT_INA_PORT, TILT_INA_PIN, TILT_INB_PORT, TILT_INB_PIN);
	INTAKE::trinary(INTAKE::stretch, STRETCH_INA_PORT, STRETCH_INA_PIN, STRETCH_INB_PORT, STRETCH_INB_PIN);
	INTAKE::trinary(INTAKE::suck, SUCK_INA_PORT, SUCK_INA_PIN, SUCK_INB_PORT, SUCK_INB_PIN);
}

