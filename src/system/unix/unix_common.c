#include"ExCommon.h"
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
#	include<regex.h>



ELTDECLSPEC Int32 ELTAPIENTRY ExCreateProcess(const ExChar* applicationName){
    pid_t pid;
    pid = fork();

    switch(pid){
        case -1:{
            fprintf(stderr,strerror(errno));
            kill(pid,9);
            return 0;
        }break;
        case 0:{
            ExChar argv[512]= {0};
            memcpy(argv, applicationName,strlen(applicationName) + 1);
            chdir(dirname(argv));
            if(execl(applicationName,basename(applicationName),NULL) == -1)
                fprintf(stderr,strerror(errno));
        }break;
        default:{
            wait(&pid);
        }break;
    }

    return True;
}


ELTDECLSPEC Int32 ELTAPIENTRY ExCreateProcessl(const ExChar* applicationName,...){
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
            fprintf(stderr,strerror(errno));
            kill(pid,9);
            return 0;

        }break;
        case 0:{
        	/*	TODO some error when arm */
            if(execv(applicationName,(const char*)applicationName + sizeof(void*) ) == -1)
                fprintf(stderr,strerror(errno));
	}break;
        default:{
            wait(&pid);
        }break;
    }

    return 1;
}




ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size){
	ExGetScreenSize(0,size);
}


ELTDECLSPEC void ELTAPIENTRY ExGetScreenSize(Uint32 index, ExSize* size){

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


ELTDECLSPEC Int32 ELTAPIENTRY ExGetScreenSizes(Uint index, Uint* num, ExSize*sizes){
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


ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect){
	ExGetScreenRect(0,rect);
}

ELTDECLSPEC void ELTAPIENTRY ExGetScreenRect(Uint32 index, ExRect* rect){
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	info = XRRGetOutputInfo (display, screen, screen->outputs[0]);
	crtc_info = XRRGetCrtcInfo (display, screen, screen->crtcs[index]);


	rect->width 	= crtc_info->width;
	rect->height 	= crtc_info->height;
	rect->x			= crtc_info->x;
	rect->y			= crtc_info->y;


	XRRFreeCrtcInfo(crtc_info);
	XRRFreeOutputInfo (info);
	XRRFreeScreenResources(screen);

}

ELTDECLSPEC Int32 ELTAPIENTRY ExGetScreenRefreshRate(Uint32 index){
	unsigned int num_sizes;
	Display*dis = XOpenDisplay(NULL);
	Window root = RootWindow(dis,index);
	//XRRScreenSize* xrrs = XRRSizes(dis, 0, &num_sizes);

	// XRRScreenConfiguration* conf = XRRGetScreenInfo(dis, root);


	//return XRRConfigCurrentRate(conf);
	return 1;

}

/*	http://hackage.haskell.org/package/bindings-GLFW-0.1.0/src/glfw/src/x11_monitor.c	*/
ELTDECLSPEC int ELTAPIENTRY ExSetScreenSize(Int32 index, Int32 width, Int32 height){
	XRRScreenResources* sr = NULL;
	XRRCrtcInfo* ci = NULL;
	XRROutputInfo* oi = NULL;
	RRMode bestMode = 0;


	sr = XRRGetScreenResources(display, DefaultRootWindow(display));
	ci = XRRGetCrtcInfo(display, sr, sr->outputs[0]);
	oi = XRRGetOutputInfo(display, sr, sr->crtcs[index]);





	XRRSetCrtcConfig(display, sr, NULL, CurrentTime, ci->x, ci->y, bestMode, ci->rotation, ci->outputs, ci->noutput );

	XRRFreeOutputInfo(oi);
	XRRFreeCrtcInfo(ci);
	XRRFreeScreenResources(sr);
}



const ExChar* ELTAPIENTRY ExGetPlatform(void){
	struct utsname name;

	if (uname(&name)){
	    printf("OS: %s\n", name.sysname);
	}
	return NULL;
}


#define _DATADIR "/sys/class/power_supply"
ELTDECLSPEC Enum ELTAPIENTRY ExGetPowerInfo(Int32* sec, Int32* pct){
	FILE *f_c, *f_f;
	long current, full;
	DIR *d;
	struct dirent *dp;

	if((d = opendir(_DATADIR)) == NULL) {
		fprintf(stderr, "opendir: %s\n", strerror(errno));
		return 3;
	}


	while((dp = readdir(d)) != NULL) {

		regex_t regex;
		//if(regcomp())

	}

    if(sec)
        *sec = 1;
    if(pct)
        *pct = 1;

    closedir(d);
	return TRUE;
}

ELTDECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 length){
	/**/
    extern char* __progname;

    memcpy(wChar,/*program_invocation_name*/__progname,length);
}

ELTDECLSPEC void ELTAPIENTRY ExGetAppliationPath(ExChar* path, Int32 length){
    //readlink()
	getcwd(path,length);
}

ELTDECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name,Int32 length){

#   if defined(EX_GNUC) || defined(EX_GNUC)
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/__progname,length);
    return name;
#   else
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/"",length);
    return name;
#   endif
}

ELTDECLSPEC ExChar* ELTAPIENTRY ExGetCurrentDirectory(void){
	ExChar cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	   fprintf(stdout, "Current working dir: %s\n", cwd);
	else
	   perror("getcwd() error");
	return cwd;

}

ELTDECLSPEC Int32 ELTAPIENTRY ExSetCurrentDirectory (const char* cdirectory){
	return chdir(cdirectory);
}



ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void){
    struct sysinfo sys_info;

    sysinfo(&sys_info);
	return sys_info.totalram;

}

ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.totalswap;
}

ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetOSName(void){
	struct utsname name;
	if(uname(&name) != EFAULT)
		return name.sysname;
	else
		return EX_TEXT("linux");

}

ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetCurrentUser(void){
	return getenv("USER");
}



ELTDECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text){

	return NULL;
}

ELTDECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void){

	return NULL;
}


ELTDECLSPEC void* ELTAPIENTRY ExDownloadURL(const ExChar* url){
	ExSocket sock = ExOpenSocket(ELT_TCP);

	if(ExConnectSocket(ExGetHostIp(url),80)){


	}
	ExCloseSocket(sock);
	return 0;
}


