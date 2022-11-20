#include "debug.h"
#include "stm_main.h"
#include "mecanum.h"

/** whether turn on debug mode **/
bool debug_mode = false;

/** debug which function **/
bool mecanum_debug = true;
bool intake_debug = false;
bool scara_debug = false;


void debug_loop(){
	while(1){
		if(mecanum_debug) mecanum.run();

	}
}
