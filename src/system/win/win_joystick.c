#include"input/elt_joystick.h"
#include<string.h>

#include<windows.h>
#include<dinput.h>
#include<xinput.h>
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")



ELTDECLSPEC Uint32 ELTAPIENTRY ExJoysticksNum(void){
	Int32 num = 0;
	Uint32 i,count;
	JOYINFO info;
	count = joyGetNumDevs();
	for(i = 0; i < count; i++){
		if(joyGetPos(JOYSTICKID1+i,&info) == JOYERR_NOERROR)
			num++;
	}
	return num;

}

ELTDECLSPEC ExHandle ELTAPIENTRY ExJoystickOpen(Int32 index){
	JOYCAPS caps;
	joyGetDevCaps(index,&caps,sizeof(caps));
	if(!GetModuleHandle(caps.szRegKey))
		return ExLoadObject(caps.szRegKey);
	else return (void*)TRUE;

}

ELTDECLSPEC int ELTAPIENTRY ExJoyStickClose(Int32 device_index){

}

ELTDECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index){
	ExGUID guid;
	JOYCAPS2W caps2;
	joyGetDevCaps(device_index,(LPJOYCAPSW)&caps2,sizeof(caps2));
	memcpy(&guid,&caps2.NameGuid,sizeof(ExGUID));

	//read(joy_id[device_index],&event,sizeof(event));
	return guid;
}

ELTDECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr){

	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps,sizeof(caps));
	return caps.szPname;
}

ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr){
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps, sizeof(caps));
	return caps.wNumButtons;
}

ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int32 device_index){
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps, sizeof(caps));
	return caps.wNumAxes;
}

ELTDECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 index,int axis){
    JOYINFO  pji;
    joyGetPos(index,&pji);
    return ((unsigned int*)&pji)[axis];
}

ELTDECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button){
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[button];
}

//http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx

