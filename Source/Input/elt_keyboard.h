/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_KEYBOARD_H
#define ELT_KEYBOARD_H
#include"./../EngineAssembly.h"
#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION 0x800
#endif
typedef Keycode ExScancode;

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/**
	// Get KeyCode name identification index
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromName(const char* name);
/**
	//	Get Key from Scancode
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromScancode(ExScancode scancode);
/**
	// Get KeyCode name
*/
extern DECLSPEC const char* ELTAPIENTRY ExGetKeyName(Keycode keycode);

/**
	// Get Window that is keyboard is focus to
*/
extern DECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void);
/**
	//
*/
extern DECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys);
/**
	//
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetModeState(void);

/**
	// is any key pressed
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKey(void);
/**
	//
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKeyDown(void);
/**
	//
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKey(const Uint32 keyCode);
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyDown(const Uint32 keyCode);
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyUp(const Uint32 keyCode);




#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
