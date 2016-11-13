#include"input/elt_joystick.h"
#include<string.h>

#include<windows.h>
#include<dinput.h>
#include<xinput.h>
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")



 unsigned int  ExJoysticksNum(void){
	int num = 0;
	unsigned int i,count;
	JOYINFO info;
	count = joyGetNumDevs();
	for(i = 0; i < count; i++){
		if(joyGetPos(JOYSTICKID1+i,&info) == JOYERR_NOERROR)
			num++;
	}
	return num;

}

 ExHandle  ExJoystickOpen(int index){
	JOYCAPS caps;
	joyGetDevCaps(index,&caps,sizeof(caps));
	if(!GetModuleHandle(caps.szRegKey))
		return ExLoadObject(caps.szRegKey);
	else return (void*)TRUE;

}

 int  ExJoyStickClose(int device_index){

}

 ExGUID  ExJoystickGetDeviceGUID(int device_index){
	ExGUID guid;
	JOYCAPS2W caps2;
	joyGetDevCaps(device_index,(LPJOYCAPSW)&caps2,sizeof(caps2));
	memcpy(&guid,&caps2.NameGuid,sizeof(ExGUID));

	//read(joy_id[device_index],&event,sizeof(event));
	return guid;
}

 const ExChar*  ExJoyStickName(unsigned int ptr){

	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps,sizeof(caps));
	return caps.szPname;
}

 int  ExJoystickNumButtons(unsigned int ptr){
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps, sizeof(caps));
	return caps.wNumButtons;
}

 int  ExJoystickNumAxis(int device_index){
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps, sizeof(caps));
	return caps.wNumAxes;
}

 short  ExJoystickGetAxis(int index,int axis){
    JOYINFO  pji;
    joyGetPos(index,&pji);
    return ((unsigned int*)&pji)[axis];
}

 unsigned char  ExJoyStickGetButton(int device_index, int button){
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[button];
}

//http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx

