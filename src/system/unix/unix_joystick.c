#include"input/elt_joystick.h"

#include <libudev.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include<linux/input.h>
#include<sys/ioctl.h>

int joy_id[4];



unsigned int ExJoysticksNum(void){
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

ExJoyStick ExJoystickOpen(int index){
	//struct js_event event;

	char device_text[sizeof("/dev/input/js0") + 10] = {0};
	sprintf(device_text, "/dev/input/js%d", index);

	joy_id[index] = open(device_text, O_RDONLY | O_SYNC);
	//read(joy_id[index],&event,sizeof(event));
	return index;
}

int ExJoyStickClose(int device_index){
    return close(joy_id[device_index]);
}

ExGUID ExJoystickGetDeviceGUID(int device_index){
	ExGUID guid;

	//read(joy_id[device_index],&event,sizeof(event));
	//JSIOCGVERSION
	return guid;
}

const ExChar* ExJoyStickName(unsigned int ptr){
	static char name[128];
	if(ioctl(joy_id[ptr], JSIOCGNAME(sizeof(name)), name) < 0){
		strncpy(name,"Unknown", sizeof(name));
	}
	return name;
}

int ExJoystickNumButtons(unsigned int ptr){
    int num_buttons;
    if(!ioctl(joy_id[ptr],JSIOCGBUTTONS,&num_buttons))
        return num_buttons;
    else
        return -1;
}

int ExJoystickNumAxis(int device_index){
    int num_axis;
    if(!ioctl(joy_id[device_index],JSIOCGAXES,&num_axis))
        return num_axis;
    else
        return -1;
}

short ExJoystickGetAxis(int index, int axis){
    struct js_event js;
    if(read(joy_id[index], &js, sizeof(struct js_event)) >= 0){
        if(js.type & JS_EVENT_AXIS){
            return js.number == axis ? js.value : 0;
        }
    }else
    	return 0;
}


unsigned char ExJoyStickGetButton(int device_index, int button){
    struct js_event js;
    if(read(joy_id[device_index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_BUTTON)
            return js.value;
    }else
    	return -1;
}


void ExGetJoySticAxisMapping(ExJoyStick joystick, ExChar* mapping, unsigned int len){
    if(!ioctl(joy_id[(unsigned int)joystick], JSIOCGAXMAP, mapping)){

    }
}

void ExSetJoySticAxisMapping(ExJoyStick joystick, const ExChar* mapping, unsigned int len){
    if(!ioctl(joy_id[(unsigned int)joystick], JSIOCSAXMAP, mapping)){

    }
    return;
}

