#include "intake.h"

namespace INTAKE{
	double tilt, stretch, suck;
}


void INTAKE::run(void){
	 /*stretch*/
	    if (INTAKE::stretch == 0){
	    	HAL_GPIO_WritePin(STRETCH_INA_PORT, STRETCH_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(STRETCH_INB_PORT, STRETCH_INB_PIN, GPIO_PIN_RESET);
	    } else if (INTAKE::stretch == -1){
	    	HAL_GPIO_WritePin(STRETCH_INA_PORT, STRETCH_INA_PIN, GPIO_PIN_SET);
	    	HAL_GPIO_WritePin(STRETCH_INB_PORT, STRETCH_INB_PIN, GPIO_PIN_RESET);
	    } else if (INTAKE::stretch == 1){
	    	HAL_GPIO_WritePin(STRETCH_INA_PORT, STRETCH_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(STRETCH_INB_PORT, STRETCH_INB_PIN, GPIO_PIN_SET);
	    }

	/*tilt*/
	    if (INTAKE::tilt == 0){
	    	HAL_GPIO_WritePin(TILT_INA_PORT, TILT_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(TILT_INB_PORT, TILT_INB_PIN, GPIO_PIN_RESET);
	    } else if (INTAKE::tilt == 1){
	    	HAL_GPIO_WritePin(TILT_INA_PORT, TILT_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(TILT_INB_PORT, TILT_INB_PIN, GPIO_PIN_SET);
	    } else if (INTAKE::tilt == -1){
	    	HAL_GPIO_WritePin(TILT_INA_PORT, TILT_INA_PIN, GPIO_PIN_SET);
	    	HAL_GPIO_WritePin(TILT_INB_PORT, TILT_INB_PIN, GPIO_PIN_RESET);
	    }

    /*suck*/
	    if (INTAKE::suck == 0){
	    	HAL_GPIO_WritePin(SUCK_INA_PORT, SUCK_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(SUCK_INB_PORT, SUCK_INB_PIN, GPIO_PIN_RESET);
	    } else if (INTAKE::suck == 1){
	    	HAL_GPIO_WritePin(SUCK_INA_PORT, SUCK_INA_PIN, GPIO_PIN_SET);
	    	HAL_GPIO_WritePin(SUCK_INB_PORT, SUCK_INB_PIN, GPIO_PIN_RESET);
	    } else if (INTAKE::suck == -1){
	    	HAL_GPIO_WritePin(SUCK_INA_PORT, SUCK_INA_PIN, GPIO_PIN_RESET);
	    	HAL_GPIO_WritePin(SUCK_INB_PORT, SUCK_INB_PIN, GPIO_PIN_SET);
	    }
}

