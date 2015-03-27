#include"ExCommon.h"
#ifdef EX_LINUX
#   include"system/unix/unix_win.h"
#   include<unistd.h>
#   include<sys/utsname.h>
#   include<sys/sysinfo.h>
#   include<errno.h>
#   include<libgen.h>
#   include<X11/Xlib.h>
#   include<X11/extensions/Xrandr.h>
#elif defined(EX_ANDROID)
#   include<unistd.h>
#   include<sys/utsname.h>
#   include<sys/sysinfo.h>
#   include<errno.h>
#   include<libgen.h>
#elif defined(EX_WINDOWS)
#	include<Windows.h>
#	include<WinInet.h>
#endif

DECLSPEC Int32 ELTAPIENTRY ExCreateProcess(const ExChar* applicationName){
#ifdef EX_WINDOWS
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
    si.cb = sizeof(si);
	if( !CreateProcess(
        applicationName,    // No module name (use command line)
        EX_TEXT(""),        // Command line
        NULL,               // Process handle not inheritable
        NULL,               // Thread handle not inheritable
        FALSE,              // Set handle inheritance to FALSE
        CREATE_NEW_PROCESS_GROUP,              // No creation flags
        NULL,               // Use parent's environment block
        NULL,               // Use parent's starting directory
        &si,                // Pointer to STARTUPINFO structure
        &pi )               // Pointer to PROCESS_INFORMATION structure
    ) {
		ExDevWindowPrintc(EX_TEXT("CreateProcess failed (%d).\n"),EX_CONSOLE_RED);
		return FALSE;
    }
	return TRUE;
#elif defined(EX_LINUX)
    pid_t pid;
    pid = fork();

    switch(pid){
        case -1:{
            fprintf(stderr,strerror(errno));
            kill(pid,9);
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
    return 1;
#endif
}
DECLSPEC Int32 ELTAPIENTRY ExCreateProcessl(const ExChar* applicationName, ...){
	va_list argptr;
	ExChar argv[1024]= {0};
	ExChar* arg_temp;
	va_start(argptr,applicationName);
#ifdef EX_WINDOWS

	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};

#ifdef EX_UNICODE
	while(arg_temp = va_arg(argptr, ExChar*)){	// while arg isn't a null variable
		wcscat(argv,(const ExChar*)arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}
#else
	while((arg_temp = va_arg(argptr, ExChar*)) != NULL){
		strcat(argv,arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}

#endif
	va_end(argptr);
    si.cb = sizeof(si);
	if( !CreateProcess(applicationName,   // No module name (use command line)
       argv,       // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NEW_PROCESS_GROUP,// No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) {
		ExDevWindowPrintc(EX_TEXT("CreateProcess failed"),EX_CONSOLE_RED);
		return FALSE;
    }

	return TRUE;
#elif defined(EX_LINUX)
    pid_t pid;
    // TODO FIX
/*	while((arg_temp = va_arg(argptr, ExChar*)) != NULL){
		strcat(argv,arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}*/

    pid = fork();
    switch(pid){
        case -1:{
            fprintf(stderr,strerror(errno));
            kill(pid,9);
        }break;
        case 0:{
            if(execv(applicationName,argptr) == -1)
                fprintf(stderr,strerror(errno));
        }break;
        default:{
            wait(&pid);
        }break;
    }
	va_end(argptr);
#endif
}

DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(struct exsize* size){
#ifdef EX_WINDOWS
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	size->width  = rect.right - rect.left;
	size->height = rect.bottom - rect.top;
#elif defined(EX_LINUX)
	Screen* scrn = DefaultScreenOfDisplay(display);
	size->width = scrn->width;
	size->height = scrn->height;
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExGetMonitorSize(Uint32 index, struct exsize* size){
#ifdef EX_WINDOWS
	//EnumDisplaySettings(
#elif defined(EX_LINUX)
	Screen* scrn = XScreenOfDisplay(display,index);
	size->width = scrn->width;
	size->height = scrn->height;
#elif defined(EX_ANDROID)

#endif
}

DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(struct exrect* rect){
#ifdef EX_WINDOWS
	GetWindowRect(GetDesktopWindow(), (LPRECT)rect);
#elif defined(EX_LINUX)
	Screen* scrn = DefaultScreenOfDisplay(display);
	rect->x = 0;
	rect->y = 0;
	rect->width = scrn->width;
	rect->height = scrn->height;
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExGetMonitorRect(Uint32 index, struct exrect* rect){
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)

#elif defined(EX_ANDROID)

#endif
}

DECLSPEC Int32 ELTAPIENTRY ExGetMonitorHz(Uint32 index){
#ifdef EX_WINDOWS
	DEVMODE mod;
	DISPLAY_DEVICE dev;
	dev = ExGetMonitor(index);
	EnumDisplaySettings(dev.DeviceName,ENUM_CURRENT_SETTINGS, &mod);
	return mod.dmDisplayFrequency;
#elif defined(EX_LINUX)
    unsigned int num_sizes;
    Display*dis = XOpenDisplay(NULL);
    Window root = RootWindow(dis,index);
    XRRScreenSize* xrrs = XRRSizes(dis, 0, &num_sizes);

    XRRScreenConfiguration* conf = XRRGetScreenInfo(dis, root);


	return XRRConfigCurrentRate(conf);
#elif defined(EX_ANDROID)

#endif
}


DECLSPEC Enum ELTAPIENTRY ExGetPowerInfo(Int32* sec, Int32* pct){
#if defined(EX_WINDOWS)
	SYSTEM_POWER_STATUS spsPwr;
	if(!GetSystemPowerStatus(&spsPwr))
		ExIsWinError(EX_TEXT("Failed to Get Power Information"));
	if(sec)
		*sec = spsPwr.BatteryLifeTime;
	if(pct)
		*pct = spsPwr.BatteryLifePercent;
#elif defined(EX_LINUX)

    if(sec)
        *sec = 1;
    if(pct)
        *pct = 1;
#elif defined(EX_ANDROID)

#endif
	return TRUE;
}

DECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 length){
#ifdef EX_WINDOWS
	ExIsError(GetModuleFileName(EX_NULL,wChar,length));
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    extern char* __progname;
    memcpy(wChar,/*program_invocation_name*/__progname,length);
#endif
	return;
}
DECLSPEC void ELTAPIENTRY ExGetAppliationPath(ExChar* wChar, Int32 length){
#ifdef EX_WINDOWS
	ExIsError(GetCurrentDirectory(length,wChar));
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    //readlink()
	getcwd(wChar,length);
#endif
	return;
}
//function manually
DECLSPEC void ELTAPIENTRY ExGetApplicationName(ExChar* name,Int32 length){
#ifdef EX_WINDOWS
	ExChar path[MAX_PATH];
	ExIsError(GetModuleFileName(EX_NULL,path,sizeof(path)));
	_wsplitpath(path,0,0,name,0);
#elif defined(EX_LINUX)
#   if defined(EX_GNUC) || defined(EX_GNUC)
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/__progname,length);
    return name;
#   else
    extern char* __progname;
    memcpy(name,/*program_invocation_name*/"",length);
    return name;
#   endif
#endif
}


DECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void){
#ifdef EX_WINDOWS
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.totalram;
#endif
}

DECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void){
#ifdef EX_WINDOWS
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalVirtual;
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    struct sysinfo sys_info;
    sysinfo(&sys_info);
	return sys_info.totalswap;
#endif
}


//InternetOpenUrl
DECLSPEC void* ELTAPIENTRY ExDownloadURL(const ExChar* url){
#ifdef EX_WINDOWS
	//LAST ERROR
	HINTERNET hOpen = NULL;
	HINTERNET hFile = NULL;
	HANDLE hOut = NULL;
	char* lpBuffer = NULL;
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;
	hOpen = InternetOpen(L"MyAgent", NULL, NULL, NULL, NULL);
	hFile = InternetOpenUrl(hOpen,url,0,0,INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE,NULL);

	//InternetReadFile(hFile,0,0,&dwBytesRead);
	lpBuffer = (char*)malloc(1024);
	InternetReadFile(hFile,(LPVOID*)lpBuffer,1024,&dwBytesRead);
	InternetCloseHandle(hFile);
	InternetCloseHandle(hOpen);
	return lpBuffer;
#elif defined(EX_LINUX)
	return 0;
#endif
}

DECLSPEC const ExChar* ELTAPIENTRY ExGetOSName(void){
#if defined(EX_WINDOWS)
	OSVERSIONINFO pOSVI;
	pOSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&pOSVI)){
		wExDevPrintf(TEXT("Failed to Get Operting System Version | %s |"),ExGetErrorMessage(GetLastError()));
	}
	// check what version this computer is running.
	if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==4))
		return EX_TEXT("Windows 10");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==3))
		return EX_TEXT("Windows 8.1");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==2))
		return EX_TEXT("Windows 8");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==1))
		return EX_TEXT("Windows 7");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows Vista");
	else if ((pOSVI.dwMajorVersion ==5)&&(pOSVI.dwMinorVersion==1))
		return EX_TEXT("Windows XP");
	else if ((pOSVI.dwMajorVersion ==5)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows 2000");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows NT 4.0");
	else if ((pOSVI.dwMajorVersion ==3)&&(pOSVI.dwMinorVersion==51))
		return EX_TEXT("Windows NT 3.51");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==90))
		return EX_TEXT("Windows ME");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==10))
		return EX_TEXT("Windows 98");
	else if((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==0))
		return TEXT("Windows 95");
	else
		return TEXT("Windows OS Unknown");
#elif defined(EX_LINUX)
    return "Linux";
	struct utsname _name;
	if(uname(&_name) != EFAULT)
		return _name.sysname;
	else return EX_TEXT("");
#elif defined(EX_ANDROID)
	return EX_TEXT("Android");
#elif defined(EX_MAC)
	return EX_TEXT("Mac OS X")
#elif defined(EX_APPLE)
	return EX_TEXT("Iphone");
#endif
}

DECLSPEC ExChar* ELTAPIENTRY ExGetCurrentUser(void){
#ifdef EX_WINDOWS
	ExChar user[MAX_PATH];
	ULong csize;
	ExIsError(GetUserName(user,&csize));
	return user;
#elif defined(EX_LINUX) || defined(EX_ANDROID)
	return getenv("USER");
#endif
}
// get clipboard text
DECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void){
#ifdef EX_WINDOWS
	HANDLE hData;
	ExChar* pszText;
	OpenClipboard(EX_NULL);
#ifdef EX_UNICODE
	hData = GetClipboardData(CF_UNICODETEXT);
	pszText = (ExChar*)GlobalLock(hData);
#else
	hData = GetClipboardData(CF_TEXT);
	pszText = (char*)GlobalLock(hData);
#endif
	GlobalUnlock( hData );
	CloseClipboard();

	return (ExChar*)pszText;
#elif defined(EX_LINUX)
	return 0;
#endif
}

DECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text){
#ifdef EX_WINDOWS
	HANDLE handle;
	void* data;
	OpenClipboard(EX_NULL);
	// create a buffer of data
	handle = GlobalAlloc(GMEM_MOVEABLE,
		sizeof(ExChar) * EX_STR_LEN(text) + sizeof(ExChar));
	data = GlobalLock(handle );
	memcpy(data,text, sizeof(ExChar) * EX_STR_LEN(text)+sizeof(ExChar));
	GlobalUnlock(handle);
#ifdef EX_UNICODE
	SetClipboardData(CF_UNICODETEXT,handle);
#else
	SetClipboardData(CF_TEXT,handle);
#endif
	CloseClipboard();
	return (data != EX_NULL);
#elif defined(EX_LINUX)
	return 0;
#endif
}

#ifdef EX_LINUX
#	include<sys/socket.h>
#endif
DECLSPEC ERESULT ELTAPIENTRY ExPutFTPFile(const ExChar* ftp, const ExChar* user, const ExChar* password,const ExChar* file, const ExChar* directory){
#ifdef EX_WINDOWS
	HINTERNET hInternet;
	HINTERNET hFtpSession;
	hInternet = InternetOpen(EX_NULL,INTERNET_OPEN_TYPE_PRECONFIG,EX_NULL,EX_NULL,0);
	if(!hInternet)
		return E_FAILURE;
	hFtpSession = InternetConnect(hInternet,(LPTSTR)ftp , INTERNET_DEFAULT_FTP_PORT, (LPTSTR)user, (LPTSTR)password, INTERNET_SERVICE_FTP, 0, 0);
	if(directory)
	FtpSetCurrentDirectory(hFtpSession,directory);
	if(!hFtpSession)
		return E_FAILURE;
	if(!FtpPutFile(hFtpSession,file,file, FTP_TRANSFER_TYPE_ASCII, 0))
		ExIsError(0);
	InternetCloseHandle(hFtpSession);
	InternetCloseHandle(hInternet);
	return TRUE;
#elif defined(EX_LINUX)
	//socket(AF_INET, SOCK_STREAM,0);
	return 0;
#endif
}
