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
#ifndef _ELT_GZ_H_
#define _ELT_GZ_H_ 1
#include"elt_file.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif

/**
 *	@Return
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExLoadZipFile(const char* archive, const char **cfilename, void **data);

/**
 *	@Return
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExSaveZipFile(const char* archive, const char **cfilename, void *data, int long size);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif


#endif
