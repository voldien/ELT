#include"ExCommon.h"
#include<malloc.h>

#include <unistd.h>
#   include"system/unix/unix_win.h"
#   include<sys/utsname.h>
#   include<sys/sysinfo.h>
#   include<errno.h>
#   include<libgen.h>
#   include<X11/Xlib.h>
#   include<X11/extensions/Xrandr.h>

DECLSPEC Int32 ELTAPIENTRY ExCreateProcess(const ExChar* applicationName){
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


DECLSPEC Int32 ELTAPIENTRY ExCreateProcessl(const ExChar* applicationName,...){
	va_list argptr;
	ExChar argv[1024]= {0};
	ExChar* arg_temp;
	va_start(argptr,applicationName);

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




DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size){
	XRRScreenResources *screen;
	//XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
//	info = XRRGetOutputInfo (display, screen, screen->outputs[0]);
	crtc_info = XRRGetCrtcInfo (display, screen, screen->crtcs[0]);


	size->width = crtc_info->width;
	size->height = crtc_info->height;

	XRRFreeCrtcInfo(crtc_info);
	//XRRFreeOutputInfo (info);
	XRRFreeScreenResources(screen);

}


DECLSPEC void ELTAPIENTRY ExGetMonitorSize(Uint32 index, ExSize* size){

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



DECLSPEC Int32 ELTAPIENTRY ExGetMonitorSizes(Uint index, Uint* num, ExSize*sizes){
	XRRScreenResources *screen;
	XRROutputInfo *info;
	XRRCrtcInfo *crtc_info;

	screen = XRRGetScreenResources (display, DefaultRootWindow(display));
	info = XRRGetOutputInfo (display, screen, screen->outputs[index]);
	if(num)
		*num = info->ncrtc;
	if(sizes){
		int x;
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


DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect){
	Screen* scrn = DefaultScreenOfDisplay(display);

	rect->x = 0;
	rect->y = 0;
	rect->width = scrn->width;
	rect->height = scrn->height;
}

DECLSPEC void ELTAPIENTRY ExGetMonitorRect(Uint32 index, ExRect* rect){


}

DECLSPEC Int32 ELTAPIENTRY ExGetMonitorHz(Uint32 index){
	unsigned int num_sizes;
	Display*dis = XOpenDisplay(NULL);
	Window root = RootWindow(dis,index);
	//XRRScreenSize* xrrs = XRRSizes(dis, 0, &num_sizes);

	// XRRScreenConfiguration* conf = XRRGetScreenInfo(dis, root);


	//return XRRConfigCurrentRate(conf);
	return 1;

}


const ExChar* ELTAPIENTRY ExGetPlatform(void){

	struct utsname name;

	if (uname(&name)){
	    printf("OS: %s\n", name.sysname);
	}
	return NULL;

}


DECLSPEC Enum ELTAPIENTRY ExGetPowerInfo(Int32* sec, Int32* pct){

    if(sec)
        *sec = 1;
    if(pct)
        *pct = 1;

	return TRUE;
}



DECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 length){
	/**/
    extern char* __progname;

    memcpy(wChar,/*program_invocation_name*/__progname,length);
}

DECLSPEC void ELTAPIENTRY ExGetAppliationPath(ExChar* path, Int32 length){
    //readlink()
	getcwd(path,length);
}

DECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name,Int32 length){

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

DECLSPEC ExChar* ELTAPIENTRY ExGetCurrentDirectory(void){
	ExChar cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	   fprintf(stdout, "Current working dir: %s\n", cwd);
	else
	   perror("getcwd() error");
	return cwd;

}

DECLSPEC Int32 ELTAPIENTRY ExSetCurrentDirectory (const char* cdirectory){
	return chdir(cdirectory);
}



DECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void){
    struct sysinfo sys_info;

    sysinfo(&sys_info);
	return sys_info.totalram;

}

DECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void){
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.totalswap;
}

DECLSPEC const ExChar* ELTAPIENTRY ExGetOSName(void){
	struct utsname name;
	if(uname(&name) != EFAULT)
		return name.sysname;
	else
		return EX_TEXT("linux");

}

DECLSPEC const ExChar* ELTAPIENTRY ExGetCurrentUser(void){
	return getenv("USER");
}



DECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text){

	return NULL;
}

DECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void){

	return NULL;
}


DECLSPEC void* ELTAPIENTRY ExDownloadURL(const ExChar* url){
	ExSocket sock = ExOpenSocket(ELT_TCP);

	if(ExConnectSocket(ExGetHostIp(url),80)){

	}
	ExCloseSocket(sock);
	return 0;
}


