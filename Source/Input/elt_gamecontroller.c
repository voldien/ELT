#include"elt_gamecontroller.h"
#include"elt_joystick.h"
#if defined(EX_WINDOWS)
	#include<Xinput.h>
	#pragma comment(lib, "xinput.lib")
#elif defined(EX_LINUX)

#endif


DECLSPEC Boolean ELTAPIENTRY ExIsGameController(Int32 joystick_index){

	return 0;
}

DECLSPEC Uint16 ELTAPIENTRY ExGameControllerGetAxis(int index, int* axis){
	//XInputGetState(index,axis);
	return 0;
}


DECLSPEC void ELTAPIENTRY ExGameControllerVibration(Int32 index, Int16 LeftMotorSpeed, Int16 RightMotorSpeed){
	//XINPUT_VIBRATION vib = {LeftMotorSpeed,RightMotorSpeed};
	//XInputSetState(index,&vib);
}
