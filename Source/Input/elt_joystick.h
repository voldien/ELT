/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_JOYSTICK_H
#define ELT_JOYSTICK_H
#include"./../EngineAssembly.h"


typedef struct ex_GUID{
	Uint8 data[16];
}ExGUID;

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	// Number of joystick
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExNumJoysticks(void);
/*
    //
*/
extern DECLSPEC void* ELTAPIENTRY ExJoystickOpen(Int32  device_index);
/*
    //
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoyStickClose(Int32 device_index);

/*
	// Get Joystick Device GUID
*/
extern DECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index);
/*
	// Get Joystick name
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr);
/*
	// Get number of buttons on a joystick
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr);
/**
    \Axis Get number of axis on joystick
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int ptr);
/**

*/
extern DECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 device_ptr,int axis);
/**
    \Button
*/
extern DECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button);


extern DECLSPEC ERESULT ELTAPIENTRY ExInitJoyStick(ExWin hwnd);


DECLSPEC void* ELTAPIENTRY GetJoyStickDeviceContext(Uint32 userIndex);


DECLSPEC void ELTAPIENTRY ExSetJoyStickState(Enum bitFlag, const Uint32 userIndex);

DECLSPEC void ELTAPIENTRY ExJoyStickShutDown(void);
DECLSPEC void ELTAPIENTRY ExJoyStickDisConnected(void);		// check which index the disconneted XBox has, to applyed to it later, if it gets connected again.
DECLSPEC void ELTAPIENTRY ExUpdateJoyStickController(void);

#ifdef __cplusplus	// C++ Environment
};
#endif
#include"elt_gamecontroller.h"
#endif
