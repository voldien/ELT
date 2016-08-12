#include"input/elt_joystick.h"
#include<string.h>

#include<windows.h>
#include<dinput.h>
#include<xinput.h>
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")



 Uint32  ExJoysticksNum(void){
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

 ExHandle  ExJoystickOpen(Int32 index){
	JOYCAPS caps;
	joyGetDevCaps(index,&caps,sizeof(caps));
	if(!GetModuleHandle(caps.szRegKey))
		return ExLoadObject(caps.szRegKey);
	else return (void*)TRUE;

}

 int  ExJoyStickClose(Int32 device_index){

}

 ExGUID  ExJoystickGetDeviceGUID(Int32 device_index){
	ExGUID guid;
	JOYCAPS2W caps2;
	joyGetDevCaps(device_index,(LPJOYCAPSW)&caps2,sizeof(caps2));
	memcpy(&guid,&caps2.NameGuid,sizeof(ExGUID));

	//read(joy_id[device_index],&event,sizeof(event));
	return guid;
}

 const ExChar*  ExJoyStickName(Uint32 ptr){

	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps,sizeof(caps));
	return caps.szPname;
}

 Int32  ExJoystickNumButtons(Uint32 ptr){
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps, sizeof(caps));
	return caps.wNumButtons;
}

 Int32  ExJoystickNumAxis(Int32 device_index){
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps, sizeof(caps));
	return caps.wNumAxes;
}

 Int16  ExJoystickGetAxis(Int32 index,int axis){
    JOYINFO  pji;
    joyGetPos(index,&pji);
    return ((unsigned int*)&pji)[axis];
}

 Uint8  ExJoyStickGetButton(Int32 device_index, int button){
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[button];
}

//http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx

