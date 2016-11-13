#include"elt_common.h"
#include<malloc.h>

#include <dirent.h>
#include <unistd.h>

#   include"system/unix/unix_win.h"
#   include<sys/utsname.h>
#   include<sys/sysinfo.h>
#   include<errno.h>
#   include<libgen.h>
#   include<X11/Xlib.h>
#   include<X11/extensions/Xrandr.h>
#include <sys/resource.h>


int ExCreateProcess(const ExChar* applicationName){

    pid_t pid;
    pid = fork();

    switch(pid){
        case -1:{
            fprintf(stderr, strerror(errno));
            kill(pid,9);
            return 0;
        }break;
        case 0:{
            ExChar argv[512]= {0};
            memcpy(argv, applicationName, strlen(applicationName) + 1);
            chdir(dirname(argv));
            if(execl(applicationName, basename(applicationName), NULL) == -1)
                fprintf(stderr,strerror(errno));
        }break;
        default:{
            wait(&pid);
        }break;
    }

    //return ExCreateProcessl(applicationName);
    return True;
}


int ExCreateProcessl(const ExChar* applicationName,...){
	va_list argptr;
	ExChar argv[1024]= {0};
	ExChar* arg_temp;
	va_start(argptr, applicationName);

    pid_t pid;
    // TODO FIX
/*	while((arg_temp = va_arg(argptr, ExChar*)) != NULL){
		strcat(argv,arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}*/

	va_end(argptr);

	/*	make a copy of the process.	*/
    pid = fork();
    switch(pid){
        case -1:{
            fprintf(stderr, strerror(errno));
            kill(pid,9);
            return 0;

        }break;
        case 0:{
        	/*	TODO some error when arm */
            if(execv(applicationName,(const char*)applicationName + sizeof(void*) ) == -1)
                fprintf(stderr, strerror(errno));
	}break;
        default:{
            wait(&pid);
        }break;
    }

    return 1;
}



void ExGetPrimaryScreenSize(ExSize* size){
	ExGetScreenSize(0, size);
}

int ExGetNumScreen(void){
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;
	int num;
	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	num = screen->ncrtc;
	XRRFreeScreenResources(screen);
	return num;
}


void ExGetScreenSize(unsigned int index, ExSize* size){

	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	info = XRRGetOutputInfo (display, screen, screen->outputs[index]);
	crtc_info = XRRGetCrtcInfo (display, screen, screen->crtcs[0]);


	size->width = crtc_info->width;
	size->height = crtc_info->height;

	XRRFreeCrtcInfo(crtc_info);
	XRRFreeOutputInfo (info);
	XRRFreeScreenResources(screen);

}


int ExGetScreenSizes(unsigned int index, unsigned int* num, ExSize*sizes){
	int x;
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	info = XRRGetOutputInfo (display, screen, screen->outputs[index]);
	if(num)
		*num = info->ncrtc;

	if(sizes){

		for(x = 0; x < info->ncrtc; x++){
			XRRCrtcInfo *crtc_info = XRRGetCrtcInfo (display, screen, screen->crtcs[x]);
			sizes[x].width = crtc_info->width;
			sizes[x].height = crtc_info->height;
			XRRFreeCrtcInfo(crtc_info);
		}
	}

	 XRRFreeOutputInfo (info);
	 XRRFreeScreenResources(screen);

	return TRUE;
}


void ExGetPrimaryScreenRect(ExRect* rect){
	ExGetScreenRect(0,rect);
}

int ExGetScreenRect(unsigned int index, ExRect* rect){
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;
	int status;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	info = XRRGetOutputInfo (display, screen, screen->outputs[0]);
	crtc_info = XRRGetCrtcInfo (display, screen, screen->crtcs[index]);


	rect->width 	= crtc_info->width;
	rect->height 	= crtc_info->height;
	rect->x			= crtc_info->x;
	rect->y			= crtc_info->y;
	status = crtc_info->noutput;

	XRRFreeCrtcInfo(crtc_info);
	XRRFreeOutputInfo (info);
	XRRFreeScreenResources(screen);
	return status;
}

int ExGetScreenRefreshRate(unsigned int index){
	unsigned int num_sizes;
	Display*dis = XOpenDisplay(NULL);
	Window root = RootWindow(dis,index);
	//XRRScreenSize* xrrs = XRRSizes(dis, 0, &num_sizes);

	// XRRScreenConfiguration* conf = XRRGetScreenInfo(dis, root);


	//return XRRConfigCurrentRate(conf);
	return 1;

}

/*	http://hackage.haskell.org/package/bindings-GLFW-0.1.0/src/glfw/src/x11_monitor.c	*/
int ExSetScreenSize(int index, int width, int height){
	XRRScreenResources* sr = NULL;
	XRRCrtcInfo* ci = NULL;
	XRROutputInfo* oi = NULL;
	RRMode bestMode = 0;

	return 0;

	sr = XRRGetScreenResources(display, DefaultRootWindow(display));
	ci = XRRGetCrtcInfo(display, sr, sr->outputs[0]);
	oi = XRRGetOutputInfo(display, sr, sr->crtcs[index]);





	XRRSetCrtcConfig(display, sr, NULL, CurrentTime, ci->x, ci->y, bestMode, ci->rotation, ci->outputs, ci->noutput );

	XRRFreeOutputInfo(oi);
	XRRFreeCrtcInfo(ci);
	XRRFreeScreenResources(sr);
}


const ExChar* ExGetPlatform(void){
	struct utsname name;
	static char os[_UTSNAME_SYSNAME_LENGTH];
	if(uname(&name) != EFAULT){
		memcpy(os, name.sysname, sizeof(os));
		return os;
	}
	else{
		return "unix";
	}
}

const char* ExGetMachine(void){
	struct utsname name;
	static char os[_UTSNAME_MACHINE_LENGTH];
	if(uname(&name) != EFAULT){
		memcpy(os, name.machine, sizeof(os));
	}
	return os;
}



void ExGetExecutePath(ExChar* wChar, int length){
	/**/
    extern char* __progname;
    memcpy(wChar,/*program_invocation_name*/__progname,length);
}

ExChar* ExGetAppliationPath(ExChar* path, int length){
	return getcwd(path, length);
}

ExChar* ExGetApplicationName(ExChar* name, int length){

#   if defined(EX_GNUC) || defined(EX_GNUC)
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/__progname, strlen(__progname) + 1 < length ? strlen(__progname) + 1 : length);
    return name;
#   else
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/"",length);
    return name;
#   endif
}




int ExGetHostname(char* hostname, unsigned int len){
	return gethostname(hostname, len);
}



ExChar* ExWideToChar(const ExWide* wchar, ExChar** cchar){
	return NULL;
}

ExWide* ExCharToWide(const ExChar* cchar, ExWide** wchar){
	return NULL;
}




unsigned long ExGetTotalSystemMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.totalram * sys_info.mem_unit;
}

/**/
unsigned long ExGetTotalFreeSystemMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.freeram;
}

unsigned long ExGetTotalUsedSystemMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return (sys_info.totalram - sys_info.freeram) * sys_info.mem_unit;
}


unsigned long ExGetProcessSystemMemory(void){
	struct rusage rusage;
	getrusage(RUSAGE_SELF, &rusage);
	return 0;
}



unsigned long ExGetTotalVirtualMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return ( sys_info.totalram + sys_info.totalswap ) * sys_info.mem_unit;
}

unsigned long ExGetTotalUsedVirtualMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return ((sys_info.totalram - sys_info.freeram)  + ( sys_info.totalswap - sys_info.freeswap) ) * sys_info.mem_unit;
}

















int ExSetClipboardText(const ExChar* text){
	return 0;
}

ExChar* ExGetClipboardText(void){

	//ExGetDisplay();
	Atom format;
	Window window;
	Window owner;
	Atom selection;
	Atom seln_type;
    int seln_format;
    unsigned long nbytes;
    unsigned long overflow;
    unsigned char *src;
	char* text;

	window = XDefaultRootWindow(display);
	Atom XA_CLIPBOARD = XInternAtom(display, "CLIPBOARD", 0);
	if(XA_CLIPBOARD == None){

	}

	text = NULL;
	owner = window;
	owner = XGetSelectionOwner(display, XA_CLIPBOARD);

	owner = DefaultRootWindow(display);
	//selection = XA_CUT_BUFFER0;
	XGetWindowProperty(display, owner, selection, 0 , INT_MAX / 4, False, format, &seln_type, &seln_format, &nbytes, &overflow, &src);


	return text;
}
