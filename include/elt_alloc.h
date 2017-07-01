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
#ifndef _ELT_ALLOC_H_
#define _ELT_ALLOC_H_ 1
#include"system.h"

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/**
 *	Get Page size.
 *
 *	@Return number of bytes per page.
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetPageSize(void);


/**
 *	Get total system memory on the system.
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetTotalSystemMemory(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetTotalFreeSystemMemory(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetTotalUsedSystemMemory(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetProcessSystemMemory(void);


/**
 *	Get total virtual memory on the system.
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetTotalVirtualMemory(void);
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetTotalUsedVirtualMemory(void);





/*	TODO move to a header with data structure!	*/
typedef struct ex_pool_allocator{
	void* next;
	void* data[];
}ExPoolAllocator;

/**
 *	Create Poll allocator.
 *	[next| data]
 *
 *	@Return
 */
extern ELTDECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize);

/**
 *	Obtain next item
 *	If return value is null, then the allocator
 *	is full
 *
 *	\allocator
 *
 *	@Return
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllocator* allocator);

/**
 *	Return
 *
 *	\allocator
 *
 *	@Return current next.
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllocator* allocator, void* data);

/**
 *	@Return
 */
extern ELTDECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolResize(ExPoolAllocator* allocator, unsigned num, unsigned int itemsize);

/**
 *
 *
 *	\allocator
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExPoolFree(ExPoolAllocator* allocator);

/**
 *	Get
 *
 *	@Return
 */
#define ExPoolIndex(alloc, index, len)	( ( alloc ) + (( index ) * ( len )  + ( index )) )

/**
 *	Get pointer .
 *
 *	@Return
 */
#define ExPoolDataIndex(alloc, data, len)	((data - alloc)



typedef struct ex_list{
	/*
	 *
	 */
	struct ex_list* next;

	/*
	 *
	 */
	struct ex_list* previous;

	/**
	 *
	 */
	void* data[];

}ExList;

/**
 *	Create double linked list.
 *
 *	@Return
 */
extern ELTDECLSPEC ExList* ELTAPIENTRY ExCreateDoubleList(ExList* list,
		unsigned int num, unsigned int itemsize);


typedef struct ex_queue {
	int x;
}ExQueue;

/**
 *	Create queue data structure.
 *
 *	@Return
 */
extern ELTDECLSPEC ExQuadTree* ELTAPIENTRY ExCreateQueue(ExList* list, unsigned int depth, unsigned int itemsize);


typedef struct ex_hash_table{
	unsigned int num;
	unsigned int k;
}ExHashTable;


#ifdef __cplusplus
}
#endif

#endif
