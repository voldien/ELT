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
#ifndef _ELT_ALLOC_H_
#define _ELT_ALLOC_H_ 1
#include"EngineAssembly.h"

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/**
    Get Page size
    @return number of bytes per page.
*/
extern DECLSPEC int ELTAPIENTRY ExGetPageSize(void);


EX_ALIGN_PREFIX(4)
typedef struct ex_pool_allactor{
	void* next;

}ExPoolAllactor;


/*	poll allocator	*/
extern DECLSPEC ExPoolAllactor* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize);

extern DECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllactor* allactor);

extern DECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllactor* allactor, void* data, unsigned int len);

extern DECLSPEC ExPoolAllactor* ELTAPIENTRY ExPoolResize(ExPoolAllactor* allcotor, unsigned num, unsigned int itemsize);

extern DECLSPEC void  ELTAPIENTRY ExPoolFree(ExPoolAllactor* allactor);

#define ExPoolIndex(alloc,index,len)	( ( alloc ) + (( index ) * ( len )  + ( index )) )
#define ExPoolDataIndex(alloc,data,len)	((data - alloc)


/**/


#ifdef __cplusplus
}
#endif

#endif
