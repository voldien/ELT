/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _EX_COMMON_H_
#define _EX_COMMON_H_ 1
#include"system/elt_win.h"
#include"EngineAssembly.h"
#include"ExAssert.h"


#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif


/*
 * 	create process
 *	@return if successfully
 */
extern DECLSPEC Int32 ELTAPIENTRY ExCreateProcess(const ExChar* applicationName);

/*
 *	create process with variable argument list
 *	Remark :last argument should be null to prevent system error.
 *	@return
*/
extern DECLSPEC Int32 ELTAPIENTRY ExCreateProcessl(const ExChar* applicationName,...);


/*
 *	Get System Primary Screen Size
 */
extern DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size);

/*
 *	sGet System Monitor
 */
extern DECLSPEC void ELTAPIENTRY ExGetMonitorSize(Uint32 index,ExSize* size);

/*
 *	Get possible resolutions for a given monitor
 */
extern DECLSPEC int ELTAPIENTRY ExGetMonitorSizes(Uint index, Uint* num, ExSize*sizes);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect);
/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExGetMonitorRect(Uint32 index, ExRect* rect);

/*
 *	Get Monitor by Index Hz
 *	@return
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetMonitorHz(Uint32 index);

/*
 *
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetPrimaryMonitorHz(void);


/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExSetScreenSize(int index, int width, int height);

/**
 *	Get Platform
 *		@return
*/
extern DECLSPEC const char* ELTAPIENTRY ExGetPlatform(void);

/**
	// Get Application Name
	@return
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name,Int32 length);

/*
 *
 */
extern DECLSPEC ExChar* ELTAPIENTRY ExGetCurrentDirectory(void);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExSetCurrentDirectory (const char* cdirectory);


/*
 *  Get Application Execute global Path.
 *   @return
 */
extern DECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 lengthSize);

/* Get Application Path where the Exe file is located. */
extern DECLSPEC void ELTAPIENTRY ExGetAppliationPath(ExChar* wChar, Int32 lengthSize);
/* Get Relative Path.*/
extern DECLSPEC void ELTAPIENTRY ExGetRelativePath(const ExChar* wChar, ExChar* Chas, Int32 lengthSize);





/**

    @return
*//*TODO make move to elt_alloc*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void);
/**

    @return
*//*TODO make move to elt_alloc*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void);






/*
	Get System OperatingSystem Os Name
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetOSName(void);



/**
	Get Current User Name
	Has to maintain later!!! TODO<>
    @return
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetCurrentUser(void);



/**
	Set Clipboard Text
*/
extern DECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text);
/**
	Set Clipboard Data
*/
extern DECLSPEC Int32 ELTAPIENTRY ExSetClipboardData(void* pdata,Uint32 csize);
/**
	Get Clipboard Text
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void);
/**
	Get Clipboard data
*/

extern DECLSPEC Int32 ELTAPIENTRY ExGetClipboardData(void* pdata);

/*
	//
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExPutFTPFile(const ExChar* ftp, const ExChar* user, const ExChar* password,const ExChar* fileconst, const ExChar* directory);


//InternetOpenUrl
extern DECLSPEC void* ELTAPIENTRY ExDownloadURL(const ExChar* url);



/*
	TODO remove or something later!
	Copy Virtual Table for C++ classes
*/
#define ExCopyVPTR(destination,source) {memcpy((void*)( destination ),(const void*) ( source ), sizeof(unsigned int));}

#ifdef  __cplusplus	/* C++ Environment */
}
#endif
#endif
