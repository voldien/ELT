/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_GAME_CONTROLLER_H
#define ELT_GAME_CONTROLLER_H
#include"./../EngineAssembly.h"
#include"elt_joystick.h"

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerAddMapping(const char* mappingString);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerAddMappinFromFile(const char* filename);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerEventState(Int32 state);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerEventState(Int32 state);

extern DECLSPEC Boolean ELTAPIENTRY ExGameControllerClose(Int32 index);
extern DECLSPEC const char* ELTAPIENTRY ExGameControlerNameForIndex(Int32 index);
extern DECLSPEC Boolean ELTAPIENTRY ExGameControllerOpen(Int32 index);
extern DECLSPEC Boolean ELTAPIENTRY ExIsGameController(Int32 joystick_index);

extern DECLSPEC Uint16 ELTAPIENTRY ExGameControllerGetAxis(int index, int* axis);


extern DECLSPEC void ELTAPIENTRY ExGameControllerVibration(Int32 index, Int16 LeftMotorSpeed, Int16 RightMotorSpeed);

extern DECLSPEC void ELTAPIENTRY ExGameControllerBattery(Int32 index,Int32 );

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif 
