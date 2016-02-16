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
#ifndef _ELT_FILE_H_
#define _ELT_FILE_H_ 1
#include"./../EngineAssembly.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/*
 *	Get file size in byte.
 *	@Return
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExGetFileSize(const ExChar* cfilname);

/*
 *	Load data by specified pathname.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExLoadFile(const ExChar* cfilename, void** data);

/*
 *	Save File by specified file name.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSaveFile(const ExChar* cfilename, void* data, unsigned int csize);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC FILE* ELTAPIENTRY ExSafeOpenWrite(const ExChar* cfilename);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC FILE* ELTAPIENTRY ExSafeOpenRead(const ExChar* cfilename);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSafeWrite(FILE *f, void* buffer, unsigned int count);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSafeRead(FILE*f, void* buffer, int count);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateDirectory(const ExChar* directory);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExRemoveDirectory(const ExChar* directory);

/*
 *	Remove file by given name.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExRemoveFile(const ExChar* cfilename);

/*
 *	Return true if file exist.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExExistFile(const ExChar* cfilename);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
