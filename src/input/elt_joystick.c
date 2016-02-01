#include"input/elt_joystick.h"
#include<string.h>


#ifdef EX_WINDOWS
	#include<windows.h>
	#include<dinput.h>
	#include<xinput.h>
	//#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "dinput8.lib")
#elif defined(EX_LINUX)
#include <libudev.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include<linux/input.h>
#include<sys/ioctl.h>

Int32 joy_id[4];
//udev* udevContext = NULL;
//udev_monitor* udevMonitor = NULL;
#elif defined(EX_ANDROID)
#   include<android/input.h>
#   include<android/keycodes.h>
#   include<android/sensor.h>
    Int32 joy_id[4];
#endif


DECLSPEC Uint32 ELTAPIENTRY ExJoysticksNum(void){
#ifdef EX_WINDOWS
	Int32 num = 0;
	Uint32 i,count;
	JOYINFO info;
	count = joyGetNumDevs();
	for(i = 0; i < count; i++){
		if(joyGetPos(JOYSTICKID1+i,&info) == JOYERR_NOERROR)
			num++;
	}
	return num;
#elif defined(EX_LINUX)
	unsigned int num;
	unsigned int x;

	for(x = 0; x < 1000;x++){
		char device_text[sizeof("/dev/input/js0") + 10] = {0};
		sprintf(device_text,"/dev/input/js%d",x);
		if(access(device_text,F_OK) != -1){
			continue;
		}
		else
			break;
	}
	return num;
#elif defined(EX_ANDROID)
	return 0;
#else
	return 0;
#endif
}

DECLSPEC void* ELTAPIENTRY ExJoystickOpen(Int32 index){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(index,&caps,sizeof(caps));
	if(!GetModuleHandle(caps.szRegKey))
		return ExLoadObject(caps.szRegKey);
	else return (void*)TRUE;
#elif defined(EX_LINUX)
	//struct js_event event;

	char device_text[sizeof("/dev/input/js0") + 10] = {0};
	sprintf(device_text,"/dev/input/js%d",index);

	joy_id[index] = open(device_text, O_RDONLY);
	//read(joy_id[index],&event,sizeof(event));
	return index;
#endif
}

DECLSPEC int ELTAPIENTRY ExJoyStickClose(Int32 device_index){
    #ifdef EX_WINDOWS

	return 0;
    #elif defined(EX_LINUX)
    close(joy_id[device_index]);
    #endif
}

DECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index){
	ExGUID guid;
#if defined(EX_WINDOWS)
	JOYCAPS2W caps2;
	joyGetDevCaps(device_index,(LPJOYCAPSW)&caps2,sizeof(caps2));
	memcpy(&guid,&caps2.NameGuid,sizeof(ExGUID));
#elif defined(EX_LINUX)

	//read(joy_id[device_index],&event,sizeof(event));
#endif
	return guid;
}

DECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps,sizeof(caps));
	return caps.szPname;
#elif defined(EX_LINUX)
	char name[128];
	if(ioctl(joy_id[ptr],JSIOCGNAME(sizeof(name)),name) < 0)
		strncpy(name,"Unknown", sizeof(name));
#ifdef EX_DEBUG
	printf(name);
#endif
	return name;
#endif
}

DECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps, sizeof(caps));
	return caps.wNumButtons;
#elif defined(EX_LINUX)
    int num_buttons;
    if(!ioctl(joy_id[ptr],JSIOCGBUTTONS,&num_buttons))
        return num_buttons;
    else
        return -1;
#endif
}
DECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int32 device_index){
    #ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps, sizeof(caps));
	return caps.wNumAxes;
    #elif defined(EX_LINUX)
    int num_axis;
    if(!ioctl(joy_id[device_index],JSIOCGAXES,&num_axis))
        return num_axis;
    else
        return -1;
    #endif
}

DECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 index,int axis){
    #ifdef EX_WINDOWS
    JOYINFO  pji;
    joyGetPos(index,&pji);
    return ((unsigned int*)&pji)[axis];
    #elif defined(EX_LINUX)
    struct js_event js;
    if(read(joy_id[index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_AXIS)
            return js.value;
    }else return -1;
    #endif
}
/**
    \Button Get joystick button
*/
DECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button){
    #ifdef EX_WINDOWS
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[button];
    #elif defined(EX_LINUX)
    struct js_event js;
    if(read(joy_id[device_index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_BUTTON)
            return js.value;
    }else return -1;
    #endif // EX_WINDOWS
}

//http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx

