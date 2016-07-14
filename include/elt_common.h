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
#ifndef _ELT_COMMON_H_
#define _ELT_COMMON_H_ 1
#include"system/elt_win.h"
#include"EngineAssembly.h"
#include"elt_assert.h"


#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/**
 *	Create process.
 *	@Return if successfully
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExCreateProcess(const ExChar* applicationName);

/**
 *	create process with variable argument list
 *	Remark :last argument should be null to prevent system error.
 *	@Return
*/
extern ELTDECLSPEC Int32 ELTAPIENTRY ExCreateProcessl(const ExChar* applicationName,...);



/**
 *	Get system primary monitor screen size.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size);

/**
 *
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetNumScreen(void);

/**
 *	Get system monitor resolution by its index.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetScreenSize(Uint32 index, ExSize* size);

/**
 *	Get possible resolutions for a given monitor.
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetScreenSizes(Uint index, Uint* num, ExSize* sizes);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect);

/*
 *
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetScreenRect(Uint32 index, ExRect* rect);

/*
 *	Get monitor hz by its index.
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetScreenRefreshRate(Uint32 index);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetPrimaryScreenRefreshRate(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetScreenSize(Int32 index, Int32 width, Int32 height);






/**
 *	Get Application Name
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name, Int32 length);

/**
 *	Get Application Execute global Path.
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar, Int32 lengthSize);

/**
 *	Get Application Path where the Exe file is located.
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetAppliationPath(ExChar* wChar, Int32 lengthSize);




/**
 *	Convert wide character encoded string to ascii encoded string.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExWideToChar(const ExWide* wchar, char** cchar);

/**
 *	Convert ascii character encoded string to wide character encoded string.
 */
extern ELTDECLSPEC char* ELTAPIENTRY ExCharToWide(const ExWide* wwchar);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif
