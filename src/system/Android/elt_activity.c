#include"system/android/elt_activity.h"
#include"elt_timer.h"


#ifdef EX_ANDROID
#include <android/window.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/configuration.h>
#include<EGL/egl.h>

/**
	entry point for normal application to be found here.
*/
extern struct android_app* ex_app;
extern ANativeActivity* activity;
extern int main(int argc,char** argv);

struct android_app* elt_app = NULL;
ANativeActivity* elt_activity = NULL;
AConfiguration* config = NULL;
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
    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

    config = AConfiguration_new();
    AConfiguration_fromAssetManager(config, ((ANativeActivity*)ExGetNativeActivity())->assetManager);

}
/**
    Initialization of Android Native
*/
void* elt_main(void* states){

    initMain();


	ExDelay(500);

	//if(main)
    return main(0,NULL);
   // else{
     //   printf("failed to find main entry point");
	//	return EXIT_FAILURE;
	//}


	return NULL;
}
/*
    OnStart
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
static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window){

}
static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window){

}


static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window){

}

static void onWindowFocusChanged(ANativeActivity* activity, int focoused){

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

static void  onLowMemory(ANativeActivity* activity){


}
/**
    entry point for Native Android.
*/
void ANativeActivity_onCreate(ANativeActivity* activity, void* saveState, size_t saveStateSize){

     elt_activity = activity;

    /**
        callbacks
    */
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
	activity->callbacks->onDestroy = ExQuit;

    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = onNativeWindowResized;

    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onContentRectChanged = onContentRectChanged;
    activity->callbacks->onConfigurationChanged = NULL;

    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onLowMemory = onLowMemory;



	ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,AWINDOW_FLAG_KEEP_SCREEN_ON);


    eglInitialize(eglGetDisplay(EGL_DEFAULT_DISPLAY),NULL,NULL);

    /*  create the main thread  */
    ExCreateThread(elt_main,0,0);


    ExDelay(1000);

    /*save the references to the pointer*/

}


#endif