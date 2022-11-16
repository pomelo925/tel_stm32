#include "reset.h"
#include "intake.h"

void RESET::receive(void){
	/* first part*/
	if ( HAL_GPIO_ReadPin(FIRST_PART_PORT, FIRST_PART_PIN) == 0) RESET::state=1;

	/* second part*/
	if (HAL_GPIO_ReadPin(SECOND_PART_PORT, SECOND_PART_PIN) == 0) RESET::state=2;

	/* third part*/
	if (HAL_GPIO_ReadPin(THIRD_PART_PORT, THIRD_PART_PIN) == 0) RESET::state=3;
}
