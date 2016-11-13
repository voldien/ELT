#include"input/elt_gamecontroller.h"
#include"input/elt_joystick.h"

#if defined(EX_WINDOWS)
	#include<xinput.h>
	#pragma comment(lib, "xinput.lib")

#elif defined(EX_LINUX)

#include<linux/joystick.h>

#endif

int ExGameControllerAddMapping(const char* mappingString){
	return 0;
}

ExBoolean ExIsGameController(int joystick_index){
	return (ExBoolean)0;
}

unsigned short ExGameControllerGetAxis(int index, int* axis){
	//XInputGetState(index,axis);
	return (unsigned short)0;
}

void ExGameControllerVibration(int index, short LeftMotorSpeed, short RightMotorSpeed){
	//XINPUT_VIBRATION vib = {LeftMotorSpeed,RightMotorSpeed};
	//XInputSetState(index,&vib);
}
