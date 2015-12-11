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
#ifdef __cplusplus //	C++ Environment
extern "C"{
#endif


/*
 *	Get file size in byte
 */
extern DECLSPEC long int ELTAPIENTRY ExGetFileSize(const char* cfilname);

/*
 *	Load data by specified pathname
 */
extern DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename, void** data);

/*
 *	Save File by specified file name
 */
extern DECLSPEC int ELTAPIENTRY ExSaveFile(const char* cfilename, void* data, unsigned int csize);

/*
 *
 */
extern DECLSPEC FILE* ELTAPIENTRY ExSafeOpenWrite(const char *cfilename);

/*
 *
 */
extern DECLSPEC FILE* ELTAPIENTRY ExSafeOpenRead(const char *cfilename);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExSafeWrite(FILE *f, void* buffer, unsigned int count);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExSafeRead(FILE*f, void* buffer, int count);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExCreateDirectory(const char* directory);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExRemoveDirectory(const char* directory);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExRemoveFile(const char* cfilename);

/*
 *
 */
extern DECLSPEC int ELTAPIENTRY ExExistFile(const char* cfilename);

#ifdef __cplusplus
}
#endif

#endif
