#include "debug.h"
#include "stm_main.h"
#include "mecanum.h"
#include "intake.h"
#include "scara.h"

/** whether turn on debug mode **/
bool debug_mode = false;

/** debug which function **/
bool mecanum_debug = false;
bool intake_debug = false;
bool scara_debug = true;


void debug_loop(){
	while(1){
		if(mecanum_debug) mecanum.run();
		if(intake_debug) INTAKE::run();
		if(scara_debug) sc.run();
	}
}
