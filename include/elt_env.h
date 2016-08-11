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
#ifndef _ELT_ENV_H_
#define _ELT_ENV_H_ 1
#include"elt_def.h"
#include"ExNT.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/**
 *	Get Current User Name
 *	Has to maintain later!!! TODO<>
 *	@Return current user as a username.
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetCurrentUser(void);

/**
 *
 *
 *	@Return 1
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetEnv(const ExChar* name, const char* pValue);

/**
 *	Allocate data for the environment data.
 *
 *	@Return none NULL String if succesfully.
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetEnv(const ExChar* name);

/**
 *	Remove environment used in the process.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExRemoveEnv(const ExChar* name);

/**
 *	Allocate data to store a copy of all environment data.
 *	@Return
 */
extern ELTDECLSPEC ExChar* ExGetAllEnv(void);

/**
 *	Free allocated environment data from ExGetEnv.
 */
extern ELTDECLSPEC void ExFreeEnv(ExChar* env);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
