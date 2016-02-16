#include"input/elt_joystick.h"

#include <libudev.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include<linux/input.h>
#include<sys/ioctl.h>

Int32 joy_id[4];



ELTDECLSPEC Uint32 ELTAPIENTRY ExJoysticksNum(void){
	unsigned int num;
	unsigned int x;

	for(x = 0; x < 1000;x++){
		char device_text[sizeof("/dev/input/js0") + 10] = {0};
		sprintf(device_text,"/dev/input/js%d",x);
		if(access(device_text, F_OK) != -1){
			continue;
		}
		else
			break;
	}
	return num;
}

ELTDECLSPEC ExHandle ELTAPIENTRY ExJoystickOpen(Int32 index){
	//struct js_event event;

	char device_text[sizeof("/dev/input/js0") + 10] = {0};
	sprintf(device_text,"/dev/input/js%d",index);

	joy_id[index] = open(device_text, O_RDONLY);
	//read(joy_id[index],&event,sizeof(event));
	return index;
}

ELTDECLSPEC int ELTAPIENTRY ExJoyStickClose(Int32 device_index){
    close(joy_id[device_index]);
}

ELTDECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index){
	ExGUID guid;

	//read(joy_id[device_index],&event,sizeof(event));

	return guid;
}

ELTDECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr){
	char name[128];
	if(ioctl(joy_id[ptr],JSIOCGNAME(sizeof(name)),name) < 0)
		strncpy(name,"Unknown", sizeof(name));

	return name;

}

ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr){

    int num_buttons;
    if(!ioctl(joy_id[ptr],JSIOCGBUTTONS,&num_buttons))
        return num_buttons;
    else
        return -1;
}

ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int32 device_index){
    int num_axis;
    if(!ioctl(joy_id[device_index],JSIOCGAXES,&num_axis))
        return num_axis;
    else
        return -1;
}

ELTDECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 index,int axis){
    struct js_event js;
    if(read(joy_id[index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_AXIS)
            return js.value;
    }else return -1;
}
/**
    \Button Get joystick button
*/
ELTDECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button){
    struct js_event js;
    if(read(joy_id[device_index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_BUTTON)
            return js.value;
    }else return -1;
}
