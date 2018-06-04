#include"elt_def.h"
#include"window.h"
#include<X11/Xlib.h>

#if defined(EX_GNUC)
#if defined(EX_LINUX)
extern void* xcbConnection;

void __attribute__ ((constructor)) my_load(void) {

}

void __attribute__ ((destructor)) my_unload(void) {
	if (display != NULL) {
		XCloseDisplay(display);
	}
}

#endif
#endif
