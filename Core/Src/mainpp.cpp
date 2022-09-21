#include "mainpp.h"
#include "mecanum.h"
#include "debug.h"
#include "ros_main.h"
#include "stm_main.h"


void main_function(){
	ROS::setup();
	STM::setup();

	while(1){
		if(debug_mode) debug_loop();
		else ROS::loop();

	}
}

