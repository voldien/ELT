#include"system/android/elt_activity.h"
#include"elt_timer.h"
#include"system/elt_egl.h"


#ifdef EX_ANDROID
//#include <android/android_native_app_glue.h>
#include <android/window.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/configuration.h>
#include <android/sensor.h>
#include <android/log.h>

#include <EGL/egl.h>
#include <jni.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOG_TAG "ELT"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__))


//#include <cpu-features.h>
/**
	entry point for normal application to be found here.
*/
extern struct android_app* ex_app;
extern ANativeActivity* activity;


struct android_app* elt_app = NULL;
ANativeActivity* elt_activity = NULL;
AConfiguration* config = NULL;
#endif



ELTDECLSPEC void* ELTAPIENTRY ExGetNativeActivity(void){
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
ELTDECLSPEC int ELTAPIENTRY main(int argc,char** argv);


void* elt_main(void* states){

	initMain();


	ExDelay(500);

	return main(0,NULL);
}
/**
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

static void onLowMemory(ANativeActivity* activity){


}




static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
	return 0;
}


static void engine_handle_cmd(struct android_app* app, int32_t cmd) {

}


void android_main(struct android_app* state) {
	//struct engine engine;
    app_dummy();
	LOGI("entering main.\n");

    //ex_app = app;
    //app_dummy();

    //ANativeActivity_onCreate(app->activity, app->savedState, app->saveStateSize);

    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
/*
    state->lastTime = now_ms();
    state->firstTime = 0.;
    state->firstFrame = 0;
    state->numFrames  = 0;
*/


	//memset(&engine, 0, sizeof(engine));


    //stats_init(&engine.stats);

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        //
        while ((ident=ALooper_pollAll(1 ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                LOGI("Engine thread destroy requested!");
                //engine_term_display(&engine);
                return;
            }
        }
        /*
        if (engine.animating) {
            engine_draw_frame(&engine);
        }
        */
    }

}

/**
    entry point for Native Android.
*/
void ANativeActivity_onCreate(ANativeActivity* activity, void* saveState, size_t saveStateSize){
	ExThread main;
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

    LOGI("callback initialized.\n");

	ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,AWINDOW_FLAG_KEEP_SCREEN_ON);


    eglInitialize(eglGetDisplay(EGL_DEFAULT_DISPLAY),NULL,NULL);


    /*  create the main thread  */
    main = ExCreateThread(elt_main,0,0);
    ExWaitThread(main,NULL);

    ExDelay(1000);

    /*save the references to the pointer*/

}


#endif
