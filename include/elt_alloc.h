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

/*
 *	Get Page size
 *  @return number of bytes per page.
 */
extern DECLSPEC int ELTAPIENTRY ExGetPageSize(void);


/*
 *	Get total system memory on the system.
 */
extern DECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void);

/*
 *	Get total virtual memory on the system.
 */
extern DECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void);



/*	TODO move to a header with data structure!	*/

EX_ALIGN_PREFIX(4)
typedef struct ex_pool_allocator{
	void* next;
}ExPoolAllocator;


/*
 *	Poll allocator
 */
extern DECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize);

/*
 *	obtain next item
 *	If return value is null, then the allocator
 *	is full
 */
extern DECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllocator* allactor);

/*
 *
 */
extern DECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllocator* allactor, void* data, unsigned int len);

/*
 *
 */
extern DECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolResize(ExPoolAllocator* allcotor, unsigned num, unsigned int itemsize);

/*
 *
 */
extern DECLSPEC void  ELTAPIENTRY ExPoolFree(ExPoolAllocator* allactor);

#define ExPoolIndex(alloc,index,len)	( ( alloc ) + (( index ) * ( len )  + ( index )) )
#define ExPoolDataIndex(alloc,data,len)	((data - alloc)


typedef struct ex_quad_tree{
	struct ex_quad_tree* t0;
	struct ex_quad_tree* t1;
	struct ex_quad_tree* t2;
	struct ex_quad_tree* t3;
	void* data[0];
}ExQuadTree;

typedef struct ex_octree_tree{

}ExOctreTree;


typedef struct ex_hash_table{

}ExHashTable;

#ifdef __cplusplus
}
#endif

#endif
