#include "debug.h"
#include "stm_main.h"
#include "mecanum.h"

/** whether turn on debug mode **/
bool debug_mode = true;

/** debug which function **/
bool mecanum_debug = true;


void debug_loop(){
	while(1){
		if(mecanum_debug) mecanum.run();
	}
}
