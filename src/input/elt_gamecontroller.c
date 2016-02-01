#include"input/elt_gamecontroller.h"
#include"input/elt_joystick.h"
#if defined(EX_WINDOWS)
	#include<xinput.h>
	#pragma comment(lib, "xinput.lib")

#elif defined(EX_LINUX)

#include<linux/joystick.h>

#endif

DECLSPEC ExBoolean ELTAPIENTRY ExIsGameController(Int32 joystick_index){
	return (ExBoolean)0;
}

DECLSPEC Uint16 ELTAPIENTRY ExGameControllerGetAxis(int index, int* axis){
	//XInputGetState(index,axis);
	return (Uint16)0;
}


DECLSPEC void ELTAPIENTRY ExGameControllerVibration(Int32 index, Int16 LeftMotorSpeed, Int16 RightMotorSpeed){
	//XINPUT_VIBRATION vib = {LeftMotorSpeed,RightMotorSpeed};
	//XInputSetState(index,&vib);
}
