#include"elt_activity.h"
#include <android/window.h>
#include <android/native_activity.h>

/*
	entry point for normal application to be found here.
*/
extern int main(int argc,char** argv);

void* main(ActivityStates* states){



	if(main)
		main(0,NULL);

	return NULL;
}



void ANativeActivity_onCreate(ANativeActivity* activity, void* saveState, size_t saveStateSize){



	activity-callbacks->OnDestroy = ExQuit;
	
	
	ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,AWINDOW_FLAG_KEEP_SCREEN_ON);

}
