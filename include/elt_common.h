/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif

/**
 *	Create process.
 *
 *	@Return if successfully
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateProcess(
		const ExChar* applicationName);

/**
 *	Create process with variable argument list
 *
 *	Remark :last argument should be null to prevent system error.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateProcessl(
		const ExChar* applicationName, ...);

/**
 *	Get system primary monitor screen size.
 *
 *	\size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenSize(ExSize* size);

/**
 *	Get number of screen
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetNumScreen(void);

/**
 *	Get system monitor resolution by its index.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetScreenSize(unsigned int index,
		ExSize* size);

/**
 *	Get possible resolutions for a given monitor.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetScreenSizes(unsigned int index,
		unsigned int* num, ExSize* sizes);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetPrimaryScreenRect(ExRect* rect);

/*
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetScreenRect(unsigned int index,
		ExRect* rect);

/*
 *	Get monitor hz by its index.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetScreenRefreshRate(unsigned int index);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetPrimaryScreenRefreshRate(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetScreenSize(int index, int width,
		int height);

/**
 *	Get Application Name
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetApplicationName(ExChar* name,
		int length);

/**
 *	Get Application Execute global Path.
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetExecutePath(ExChar* wChar,
		int lengthSize);

/**
 *	Get Application Path where the Exe file is located.
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetAppliationPath(ExChar* wChar,
		int lengthSize);

/**
 *	Get hostname.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetHostname(char* hostname,
		unsigned int len);

/**
 *	Convert wide character encoded string to ascii encoded string.
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExWideToChar(const ExWide* wchar,
		ExChar** cchar);

/**
 *	Convert ascii character encoded string to wide character encoded string.
 *
 *	@Return
 */
extern ELTDECLSPEC ExWide* ELTAPIENTRY ExCharToWide(const ExChar* cchar,
		ExWide** wchar);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif
