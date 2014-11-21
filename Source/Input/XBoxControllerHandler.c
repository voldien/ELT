#include"XBoxControllerHandler.h"
#include<Cmd/mathlib.h>

	#if defined(EX_WINDOWS)
#       include<dinput.h>
#       include<XInput.h>
#       pragma comment(lib, "xinput.lib")
	#endif
typedef struct _xBoxStructor{
	//XINPUT_STATE p_XboxControllers[EX_CONTROLLER_MAX_COUNT];
	Boolean enabled[EX_CONTROLLER_MAX_COUNT];
}XBoxDesc;
extern XBoxDesc* m_XBoxControllers;
XBoxDesc* m_XBoxControllers = EX_NULL;

#define Magnitude(x1,x2) (x1 * x1 + x2 * x2)

void* GetXBoxHandler(void){
	return m_XBoxControllers;
}
ERESULT ExInitXController(void){
#ifdef EX_WINDOWS
	Boolean xBoxCIndex[EX_CONTROLLER_MAX_COUNT];
	memset(xBoxCIndex,0, sizeof(xBoxCIndex));
	Uint8 xBoxCount = 0;
	for(Int x = 0; x < EX_CONTROLLER_MAX_COUNT; x++){
		XINPUT_STATE xControllerState;
		memset(&xControllerState, 0, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(x, &xControllerState);
		if(result == ERROR_SUCCESS){
			// there is !
			xBoxCIndex[x] = TRUE;
			xBoxCount++;
		}
		else{
			// was the xBox Previusly Connected.
			if((m_XBoxControllers->enabled[x] & EX_CONTROLLER_ENABLED) != 0){

			}
		}
	}
	if(!m_XBoxControllers){
		//ZeroPointer(m_XBoxControllers,sizeof(XBoxDesc));
	}
	for(Uint x = 0; x < EX_CONTROLLER_MAX_COUNT; x++){
		memset(m_XBoxControllers->p_XboxControllers,0,SIZEOF(XINPUT_STATE) * EX_CONTROLLER_MAX_COUNT);
		if(xBoxCIndex[x] == TRUE){
			XInputGetState(x, &m_XBoxControllers->p_XboxControllers[x]);
			m_XBoxControllers->enabled[x] = xBoxCIndex[x] | EX_CONTROLLER_ENABLED;
		}
		else
			m_XBoxControllers->enabled[x] = FALSE;
		continue;
	}
#endif
	return TRUE;
}
DECLSPEC ERESULT ELTAPIENTRY ExInit_XController(const Uint userIndex){

	return 0;
}

void ExXDisConnected(void){		// check which index the disconneted XBox has, to applyed to it later, if it gets connected again.
#ifdef EX_WINDOWS
	for(Uint x = 0; x < EX_CONTROLLER_MAX_COUNT; x++){
		XINPUT_STATE xControllerState;
		memset(&xControllerState, 0, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(x, &xControllerState);
		continue;
	}
#endif
	return;
}
void ExXShutDown(void){
#ifdef EX_WINDOWS
	for(Uint x = 0; x < EX_CONTROLLER_MAX_COUNT; x++){		// Reset Controll Vibration Value!
		XINPUT_VIBRATION vb = {0};
		XInputSetState(x,&vb);
		continue;
	}
#endif
	return;
}

void ExUpdateXControllers(void){
#ifdef EX_WINDOWS
	if(m_XBoxControllers == EX_NULL)return;
	for(Uint x = 0; x < EX_CONTROLLER_MAX_COUNT; x++){
		if(m_XBoxControllers->enabled[x] == TRUE ){
			XInputGetState(x, &m_XBoxControllers->p_XboxControllers[x]);
		}
		continue;
	}
#endif
	return;
}
//void ELTAPIFASTENTRY ExUpdateXController(Uint userIndex){
//#ifdef EX_WINDOWS
//	if(m_XBoxControllers->enabled[userIndex] != FALSE){
//		XInputGetState(userIndex, &m_XBoxControllers->p_XboxControllers[userIndex]);
//	}
//#endif
//	return;
//}

void ExSetXVibration(Ushort leftMotor, Ushort rightMotor, Uint userIndex){
#ifdef EX_WINDOWS
	XINPUT_VIBRATION _vib = {0,0};
	_vib.wLeftMotorSpeed = leftMotor;
	_vib.wRightMotorSpeed = rightMotor;
	DWORD error = XInputSetState(userIndex, &_vib);
#endif
	return;
}

Float ExgetLMagnitude(Uint8 userIndex){
#ifdef EX_WINDOWS
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
	Float LX = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLX;
	Float LY = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLY;
	Float mag = (Float)Magnitude(LX,LY);

	if((Ushort)mag > (Ushort)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){
		if(mag > 32767) mag = 32767.0f;

		mag -= (Float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		return ((Float)mag / (Float)((32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)));
	}
	else{
		return 0.0f;
	}
#endif
}
Float ExgetRMagnitude(Uint8 userIndex){
#ifdef EX_WINDOWS
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
	Float RX = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRX;
	Float RY = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRY;
	Float mag = Magnitude(RX,RY);

	if(mag > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
		if(mag > 32767) mag =32767;

		mag -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

		return ((Float)mag / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	}
	else{
		return 0.0f;
	}
#endif
}

Float ExGetXLX(Uint8 userIndex){
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
#ifdef EX_WINDOWS
	return m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLX;
#endif
}
Float ExGetXLY(Uint8 userIndex){
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
#ifdef EX_WINDOWS
	return m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLY;
#endif
}
Float ExGetXRX(Uint8 userIndex){
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
#ifdef EX_WINDOWS
	return m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRX;
#endif
}
Float ExGetXRY(Uint8 userIndex){
	if(m_XBoxControllers->enabled[userIndex] == FALSE)
		return 0.0f;
#ifdef EX_WINDOWS
	return m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRY;
#endif
}

//vec2 ExgetLDirection(Uint8 userIndex){
//	if(m_XBoxControllers->enabled[userIndex] == FALSE)
//		return vec2();
//	vec2 r;
//	r.x = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLX;
//	r.y = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbLY;
//	Float mag = ExgetLMagnitude(userIndex) * Magnitude(r.x, r.y);
//	if(mag == 0.0f) return vec2();
//	r.x /= mag;
//	r.y /= mag;
//	return r;
//}
//vec2 ExgetRDirection(Uint8 userIndex){
//	if(m_XBoxControllers->enabled[userIndex] == FALSE)
//		return vec2();
//	vec2 r;
//	r.x = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRX;
//	r.y = m_XBoxControllers->p_XboxControllers[userIndex].Gamepad.sThumbRY;
//	Float mag = ExgetRMagnitude(userIndex) * Magnitude(r.x,r.y);
//	if(mag == 0.0f) return vec2();
//	r.x = r.x / mag;
//	r.y = r.y / mag;
//	return r;
//}

Boolean ExXIsPad(Uint keyCode, Uint index){
	if(m_XBoxControllers->enabled[index] == FALSE)return FALSE;
#ifdef EX_WINDOWS
	else return (m_XBoxControllers->p_XboxControllers[index].Gamepad.wButtons & keyCode) ? TRUE : FALSE;
#endif
}
Boolean ExXIsPadDown(Uint keyCode, Uint index){
	if(m_XBoxControllers->enabled[index] == FALSE)return FALSE;
#ifdef EX_WINDOWS
	else return (m_XBoxControllers->p_XboxControllers[index].Gamepad.wButtons & keyCode) ? TRUE : FALSE;
#endif
}
Boolean ExXIsPadUp(Uint keyCode, Uint index){
	//p_XboxControllers[index]->Gamepad.wButtons
	return TRUE;
}

void ExGetXBatteryLevel(Uint userIndex){
#ifdef EX_WINDOWS
	XINPUT_BATTERY_INFORMATION batinfo;
	XInputGetBatteryInformation(0,userIndex,&batinfo);
#endif

	return;
}
Uint8 ExGetXBatteryType(Uint userIndex){
#ifdef EX_WINDOWS
	XINPUT_BATTERY_INFORMATION batinfo;
	XInputGetBatteryInformation(0,userIndex,&batinfo);

	return batinfo.BatteryType;
#endif
	return 0;
}
/*
ExGUID* ExGetXSoundCaptureGUID(Uint userIndex){
	GUID* soundGuid = EX_NULL;
	GUID* renderGuid = EX_NULL;
	XInputGetDSoundAudioDeviceGuids(userIndex, soundGuid,renderGuid);
	return (ExGUID*)soundGuid;
}
ExGUID* ExGetXSoundRenderGUID(Uint userIndex){
	GUID* soundGuid = EX_NULL;
	GUID* renderGuid = EX_NULL;
	XInputGetDSoundAudioDeviceGuids(userIndex, soundGuid,renderGuid);
	return (ExGUID*)renderGuid;
}
*/
void ExSetXInputEnabled(Boolean enabled){
#ifdef EX_WINDOWS
	XInputEnable(enabled);
#endif
	return;
}
Boolean ExGetIsXWireLess(Uint userIndex){
#ifdef EX_WINDOWS
	XINPUT_CAPABILITIES  cap;
	XInputGetCapabilities(userIndex, 0,&cap);
	return (cap.Flags & 0) != 0 ? TRUE : FALSE;
#endif
	return 0;
}
Boolean ExGetSupportVoice(Uint userIndex){
#ifdef EX_WINDOWS
	XINPUT_CAPABILITIES  cap;
	XInputGetCapabilities(userIndex, 0,&cap);
	return (cap.Flags & XINPUT_CAPS_VOICE_SUPPORTED) != 0 ? TRUE : FALSE;
#endif
	return 0;
}
