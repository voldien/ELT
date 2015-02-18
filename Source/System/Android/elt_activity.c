#include"elt_activity.h"

#ifdef EX_ANDROID
#include <android/window.h>
#include <android/native_activity.h>

/*
	entry point for normal application to be found here.
*/
extern struct android_app* ex_app;
extern ANativeActivity* activity;
extern int main(int argc,char** argv);

struct android_app* elt_app;
ANativeActivity* elt_activity;
#endif

DECLSPEC void* ELTAPIENTRY ExGetNativeActivity(void){
#ifdef EX_ANDROID
    return elt_activity;
#else
    return NULL;
#endif
}




#ifdef EX_ANDROID
/**
    Initialization of Android Native
*/
void* elt_main(void* states){

	if(main)
		main(0,NULL);

	return NULL;
}



void ANativeActivity_onCreate(ANativeActivity* activity, void* saveState, size_t saveStateSize){



	activity->callbacks->onDestroy = ExQuit;


	ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,AWINDOW_FLAG_KEEP_SCREEN_ON);


    /*  create the main thread  */
    ExCreateThread(elt_main,0,0);

    /*save the references to the pointer*/
    elt_activity = activity;
}


#endif
