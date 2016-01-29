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


#ifdef __cplusplus	/*	C++ Environment	*/
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
 *	Get system primary monitor screen size.
 */
extern DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size);

/*
 *	Get system monitor resolution by its index.
 */
extern DECLSPEC void ELTAPIENTRY ExGetMonitorSize(Uint32 index, ExSize* size);

/*
 *	Get possible resolutions for a given monitor.
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetMonitorSizes(Uint index, Uint* num, ExSize* sizes);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExGetMonitorRect(Uint32 index, ExRect* rect);

/*
 *	Get monitor hz by its index.
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
extern DECLSPEC int ELTAPIENTRY ExSetScreenSize(Int32 index, Int32 width, Int32 height);

/*
 *	Get Platform
 *	@return
 */
extern DECLSPEC const char* ELTAPIENTRY ExGetPlatform(void);



/*
 *	Get Application Name
 *	@return
 */
extern DECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name, Int32 length);


/*
 *
 *	@return
 */
extern DECLSPEC ExChar* ELTAPIENTRY ExGetCurrentDirectory(void);

/*
 *
 *	@return
 */
extern DECLSPEC int ELTAPIENTRY ExSetCurrentDirectory(const ExChar* cdirectory);



/*
 *  Get Application Execute global Path.
 *   @return
 */
extern DECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 lengthSize);

/*
 *	Get Application Path where the Exe file is located.
 */
extern DECLSPEC void ELTAPIENTRY ExGetAppliationPath(ExChar* wChar, Int32 lengthSize);

/*
 *	Get Relative Path.
 */
extern DECLSPEC void ELTAPIENTRY ExGetRelativePath(const ExChar* wChar, ExChar* Chas, Int32 lengthSize);





/*
 *	Get System OperatingSystem Os Name
 */
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetOSName(void);



/*
 *	Get Current User Name
 *	Has to maintain later!!! TODO<>
 *	@return
 */
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetCurrentUser(void);


//extern DECLSPEC void ELTAPIENTRY ExUnicodeToAscii(const WCHAR* wchar, char** cchar);
//extern DECLSPEC char* ELTAPIENTRY ExConvertAscii(const WCHAR* wwchar);



/*
 *	Set clipboard text.
 */
extern DECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text);

/*
 *	Set clipboard data.
 */
extern DECLSPEC Int32 ELTAPIENTRY ExSetClipboardData(void* pdata,Uint32 csize);

/*
 *	Get clipboard text.
 */
extern DECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void);

/*
 *	Get clipboard data.
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetClipboardData(void* pdata);

/*
 *	InternetOpenUrl
 */
extern DECLSPEC void* ELTAPIENTRY ExDownloadURL(const ExChar* url);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif
