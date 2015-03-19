/*
========================================================================
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
/**
	Get file size in bytes
*/
extern DECLSPEC long ELTAPIENTRY ExGetFileSize(const char* cfilname);
/**
	Load data by specified pathname
*/
extern DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename,void** data);
/**
	Save File by specified file name
*/
extern DECLSPEC int ELTAPIENTRY ExSaveFile(const char* cfilename, void* data, unsigned int csize);


#ifdef __cplusplus
}
#endif

#endif // _ELT_FILE_H
