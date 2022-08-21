#include "stm_main.h"
#include "dc_motor.h"
#include "mecanum.h"

void STM::setup(void){
	DC_motor_init();
}

void STM::run_mecanum(void){
	mecanum.run();
}
