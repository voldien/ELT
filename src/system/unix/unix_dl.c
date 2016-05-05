#include"EngineAssembly.h"
#include"elt_def.h"



#if defined(EX_GNUC)
#if defined(EX_LINUX)
extern void* xcbConnection;

void __attribute__ ((constructor)) my_load(void){

    display = XOpenDisplay(getenv("DISPLAY"));
    if(!display){
        //ExError("couldn't open Display\n");
    }

    if(XInitThreads() == 0){
    	printf("Failed to init multithreading support\n");
    }

    /**/
	xcbConnection = XGetXCBConnection(display);
	if(xcbConnection){

	}
}

void __attribute__ ((destructor)) my_unload(void){
	if(display)
		XCloseDisplay(display);
}
#endif
#endif
