#include "reset.h"
#include "intake.h"

namespace MYRESET{
	int state=0;
}

int apple =0, banana=0, cookie=0;

void MYRESET::receive(void){

	apple = HAL_GPIO_ReadPin(FIRST_PART_PORT, FIRST_PART_PIN);
	banana = apple;
	if(banana!=apple)cookie++;

	/* first part*/
	if (HAL_GPIO_ReadPin(THIRD_PART_PORT, THIRD_PART_PIN) == 0)MYRESET::state=3;

	/* second part*/
	else if (HAL_GPIO_ReadPin(SECOND_PART_PORT, SECOND_PART_PIN) == 0) MYRESET::state=2;

	/* third part*/
	else if (HAL_GPIO_ReadPin(FIRST_PART_PORT, FIRST_PART_PIN) == 0) MYRESET::state=1;

	else MYRESET::state=0;
}



