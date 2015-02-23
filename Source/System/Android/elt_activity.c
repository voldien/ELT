#include"elt_activity.h"
#include"./../../elt_timer.h"
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
static void initMain(void){


}
/**
    Initialization of Android Native
*/
void* elt_main(void* states){
		
	ExDelay(500);


	if(main)
		return main(0,NULL);
    	else{
	printf("failed to find main entry point");
		return EXIT_FAILURE;
	}
}
/*

*/
static void onStart(ANativeActivity* activity){

}
static void onResume(ANativeActivity* activity){

}
static void onPause(ANativeActivity* activity){

}
static void onStop(ANativeActivity* activity){

}
static void onDestroy(ANativeActivity* activity){

}
static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window){

}
static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue){
/*    int (*processEvent)(int fd, int events, void* data);
    AInputQueue_attachLooper(queue,
                            ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS),
                             1,
                             processEvent,
                              NULL);
*/
}
static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue){
    AInputQueue_detachLooper(queue);
}
static void onContentRectChanged(ANativeActivity* activity, const ARect* rect){

}
static void onSaveInstanceState(ANativeActivity* activity, size_t* outlen){

}
/**
    entry point for Native Android.
*/
void ANativeActivity_onCreate(ANativeActivity* activity, void* saveState, size_t saveStateSize){
    ExPrintf("on Create");

    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onResume = onPause;
    activity->callbacks->onStop = onStop;
	activity->callbacks->onDestroy = ExQuit;


	activity->callbacks->onSaveInstanceState = onSaveInstanceState;


	ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,AWINDOW_FLAG_KEEP_SCREEN_ON);


    /*  create the main thread  */
    ExCreateThread(elt_main,0,0);

    /*save the references to the pointer*/
    elt_activity = activity;
}


#endif
